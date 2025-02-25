Dialog:MovelStatus(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new id = GetPVarInt(playerid, "CasaMovel"),
        idx = GetPVarInt(playerid, "MovelSlot"),
        Mensagem[128];

    if(cMovel[id][idx][cStatus] == 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse m�vel n�o chegou at� sua casa ainda.");
    
    switch(listitem)
    {
        case 0:
        {
            if(cMovel[id][idx][cAtivado] == true)
            {
                format(Mensagem, sizeof(Mensagem), "UPDATE `moveis` SET `Ativado` = 0 WHERE `Casa` = %d AND `MaxID` = %d", id, idx);
                mysql_query(IDConexao, Mensagem, false);
                if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao guardar esse m�vel");
                cMovel[id][idx][cAtivado] = false;
                DestroyDynamicObjectEx(cMovel[id][idx][cMovelID]); 
                format(Mensagem, sizeof(Mensagem), "| M�VEL | Voc� guardou o m�vel %s", cMovel[id][idx][cMovelNome]);
                SendClientMessage(playerid, 0xFFA500FF, Mensagem);
                return 1;
            }

            format(Mensagem, sizeof(Mensagem), "UPDATE `moveis` SET `Ativado` = 1 WHERE `Casa` = %d AND `MaxID` = %d", id, idx);
            mysql_query(IDConexao, Mensagem, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao colocar esse m�vel");

            if(cMovel[id][idx][MovelX] == 0.0 && cMovel[id][idx][MovelY] == 0.0 && cMovel[id][idx][MovelZ] == 0.0){
                GetPlayerPos(playerid, cMovel[id][idx][MovelX], cMovel[id][idx][MovelY], cMovel[id][idx][MovelZ]);
                cMovel[id][idx][MovelX] += 1.0; 
            }
            cMovel[id][idx][cAtivado] = true;

            SelecionarMovel(playerid, id, idx);

            cMovel[id][idx][cMovelID] = CreateDynamicObject(cMovel[id][idx][cMovelObjeto], cMovel[id][idx][MovelX], cMovel[id][idx][MovelY], cMovel[id][idx][MovelZ], cMovel[id][idx][MovelRx], cMovel[id][idx][MovelRy], cMovel[id][idx][MovelRz], PegarVirtualCasa(id), PegarInteriorCasa(id), -1, 120.0, 120.0, -1);
            format(Mensagem, sizeof(Mensagem), "| M�VEL | Voc� adicionou o m�vel %s", cMovel[id][idx][cMovelNome]);
            SendClientMessage(playerid, 0xFFA500FF, Mensagem);
        }
        case 1:
        {
            if(cMovel[id][idx][cAtivado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o colocou o m�vel na casa");
            new Float:mmPos[3],
                Enviar[148];
            GetPlayerPos(playerid, mmPos[0], mmPos[1], mmPos[2]);
            format(Enviar, sizeof(Enviar), "UPDATE `moveis` SET `PosX` = %f, `PosY` = %f, `PosZ` = %f WHERE `Casa` = %d AND `MaxID` = %d", mmPos[0], mmPos[1], mmPos[2], id, idx);
            mysql_query(IDConexao, Enviar, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao puxar esse m�vel");

            SelecionarMovel(playerid, id, idx);

            cMovel[id][idx][MovelX] = mmPos[0];
            cMovel[id][idx][MovelY] = mmPos[1];
            cMovel[id][idx][MovelZ] = mmPos[2];
            cMovel[id][idx][MovelX] += 3;
            SetDynamicObjectPos(cMovel[id][idx][cMovelID], mmPos[0], mmPos[1], mmPos[2]);
            SendClientMessage(playerid, -1, "| M�VEL | Voc� puxou o m�vel at� sua localiza��o");
        }
        case 2:
        {
            if(cMovel[id][idx][cAtivado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o colocou o m�vel na casa");
            SetPVarInt(playerid, "ColocandoMovel", 1);
            SetPVarInt(playerid, "MovelID", cMovel[id][idx][cMovelID]);
            EditDynamicObject(playerid, cMovel[id][idx][cMovelID]);
        }
        case 3:
        {
            if(strcmp(pCasa[id][cDono], PegarNick(playerid))) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
            if(pCasa[id][cJPreco] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Sua casa est� a venda, portanto voc� n�o pode remover esse m�vel");

            format(Mensagem, sizeof(Mensagem), "DELETE FROM `moveis` WHERE `Casa` = %d AND `MaxID` = %d", id, idx);
            mysql_query(IDConexao, Mensagem, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao guardar esse m�vel");
            
            format(Mensagem, sizeof(Mensagem), "| M�VEL | Voc� deletou o m�vel %s da sua casa.", cMovel[id][idx][cMovelNome]);
            SendClientMessage(playerid, 0xFFA500FF, Mensagem);

            // Limpando Informa��es
            if(cMovel[id][idx][cAtivado] == true) DestroyDynamicObjectEx(cMovel[id][idx][cMovelID]);
            cMovel[id][idx][cAtivado] = false;
            stringclear(cMovel[id][idx][cMovelNome]);
            cMovel[id][idx][cMovelObjeto] = 0;
            cMovel[id][idx][cmPreco] = 0;
            cMovel[id][idx][cmPrecoCoins] = 0;
            cMovel[id][idx][MovelX] = 0.0;
            cMovel[id][idx][MovelY] = 0.0;
            cMovel[id][idx][MovelZ] = 0.0;
            cMovel[id][idx][MovelRx] = 0.0;
            cMovel[id][idx][MovelRy] = 0.0;
            cMovel[id][idx][MovelRz] = 0.0;
        }
        case 4: return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Op��o desativada pelo desenvolvedor");
    }
    return 1;
}

Dialog:MoveisMenuAdmin(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new obj;
    if(sscanf(inputtext, "d", obj)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Coloque apenas n�meros");

    new id = GetPVarInt(playerid, "CasaMovel"),
        idx;
    idx = PegarMovel(id);
    if(idx == -1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | N�o h� mais espa�o nessa casa para m�veis");
    AdicionarMovelCasa(id, idx, obj, GetObjectName(obj), 500, 20, true);
    return 1;
}

Dialog:MoveisMenu(playerid, response, listitem, inputtext[]) 
{
    if(!response) return 1;
    new ksa = GetPVarInt(playerid, "AtlAAAAAA"),
        id = GetPVarInt(playerid, "CasaMovel"),
        select;
    ksa -= 10;
    for(new i=ksa; i < MAX_MOVEIS; i++)
    {
        if(select != listitem){
            select++;
            continue;
        }
        if(select >= 10 && select < MAX_MOVEIS) LoadDialogMoveis(playerid, id);
        else SelecionarMovel(playerid, id, i);
        break;
    }
    return 1;
}

