CMD:criarfabrica(playerid)
{
    if(Jogador[playerid][Admin] < 7) return 0;
    new Dialog[148];
    strcat(Dialog, "F�brica de Armas\n");
    strcat(Dialog, "F�brica de Roupas\n");
    strcat(Dialog, "F�brica de Diversos\n");
    strcat(Dialog, "F�brica de Ve�culos");
    Dialog_Show(playerid, FabricaCriacao, DIALOG_STYLE_TABLIST, "{FF0000}Cria��o", Dialog, "Selecionar", "Fechar");
    return 1;
}

CMD:liberarfabrica(playerid, params[]){
    if(Jogador[playerid][Admin] < 5) return 0;
    new id;
    if(sscanf(params, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /LiberarFabrica [ID]");
    if(pFabrica[id][Colocado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa f�brica n�o existe");
    if(!strcmp(pFabrica[id][fDono], "*")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa f�brica n�o tem propriet�rio");

    LiberarFabricaSQL(id);
    AtualizarFabrica(id);
    return 1;
}

CMD:removerfabrica(playerid, params[]){
    if(Jogador[playerid][Admin] < 7) return 0;
    new id;
    if(sscanf(params, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /RemoverFabrica [ID]");
    if(pFabrica[id][Colocado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa f�brica n�o existe");
    SqlRemoverFabrica(id);
    return 1;
}

Dialog:FabricaCriacao(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    SetPVarInt(playerid, "FabricaType", listitem);
    Dialog_Show(playerid, FabricaPrecoEx, DIALOG_STYLE_INPUT, "{FF0000}Pre�o", "Coloque abaixo o pre�o da f�brica", "Confirmar", "Cancelar");
    return 1;
}

Dialog:FabricaPrecoEx(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new precogx;
    if(sscanf(inputtext, "d", precogx)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� colocou um valor inv�lido");
    new id = PegarFabricaID(),
        Float:Hakb[3],
        Query[240];
    GetPlayerPos(playerid, Hakb[0], Hakb[1], Hakb[2]);
    format(Query, sizeof(Query), "INSERT INTO `fabricas` (`Numero`, `Dono`, `PosicaoX`, `PosicaoY`, `PosicaoZ`, `Preco`, `Liquido`, `Reparo`, `Tipo`) VALUES (%d, '*', %f, %f, %f, %d, 100, 100, %d)", id, Hakb[0], Hakb[1], Hakb[2], precogx, GetPVarInt(playerid, "FabricaType"));
    mysql_query(IDConexao, Query, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema na cria��o");

    pFabrica[id][FabricaPreco] = precogx;
    pFabrica[id][fPosicaoX] = Hakb[0];
    pFabrica[id][fPosicaoY] = Hakb[1];
    pFabrica[id][fPosicaoZ] = Hakb[2];
    pFabrica[id][LiquidoTonel] = 100;
    pFabrica[id][ReparoTonel] = 100;
    pFabrica[id][FabricaTipo] = GetPVarInt(playerid, "FabricaType");
    format(pFabrica[id][fDono], 30, "*");
    AdicionarFabrica(id); 

    format(Query, sizeof(Query), "| F�BRICA | Voc� criou uma f�brica ID %d", id);
    SendClientMessage(playerid, -1, Query);
    return 1;
}