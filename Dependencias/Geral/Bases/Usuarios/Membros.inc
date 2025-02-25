enum CompraVeiculoBase
{
    ModeloX,
    PrecoX,
    bool:CoinX
};

new BaseLoja[][CompraVeiculoBase] =
{
    {609, 6000, false}, // Boxville
    {412, 60000, false}, // Voodoo
    {445, 60000, false}, // Admiral
    {466, 65000, false}, // Glendale
    {482, 75000, false}, // Burrito
    {560, 95000, false}, // Sultan
    {468, 4000, true} // Sanchez
};

Dialog:AdicionarMembroBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new id;
    if(sscanf(inputtext, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador ID Inv�lido.");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o conectado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o est� na cidade.");

    new idbase = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(idbase, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return 1;

    if(GetPVarInt(id, "InteriorPersonalizadoID") != idbase && Jogador[id][uInteriorEx] != 9) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o est� dentro da sua base.");
    if(!IsPlayerInRangeOfPoint(id, 10.0, 2120.1702,-2273.7041,20.6719)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o est� perto da porta.");
    if(Jogador[id][BaseID] != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse(a) jogador(a) j� faz parte de uma base");

    new idx = GetPVarInt(playerid, "membroidx");
    if(bMembro[idbase][idx][TemMembro] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa vaga j� foi ocupada por um(a) membro(a)");

    new Enviar[128];
    format(Enviar, sizeof(Enviar), "INSERT INTO `basemembros` (`Nome`, `BaseID`, `PosicaoID`) VALUES ('%s', %d, %d)", EscapeString(PegarNick(id)), idbase, idx);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao adicionar esse(a) membro(a)");

    bMembro[idbase][idx][TemMembro] = true;
    format(bMembro[idbase][idx][bNome], 30, PegarNick(id));
    Jogador[id][BaseID] = idbase;

    format(Enviar, sizeof(Enviar), "| BASE | Voc� foi recrutado(a) pelo(a) %s para a base %s", PegarNick(playerid), Base[idbase][BaseNome]);
    SendClientMessage(id, 0xFFA500FF, Enviar);

    format(Enviar, sizeof(Enviar), "| BASE | Voc� recrutou o(a) %s para sua base", PegarNick(id));
    SendClientMessage(playerid, 0xFFA500FF, Enviar);
    return 1;
}

Dialog:CargoMembro(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm != 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para alterar cargos");
    new idx = GetPVarInt(playerid, "membroidx");
    if(bMembro[id][idx][TemMembro] == false) return 1;
    if(bMembro[id][idx][BaseCargo] == listitem) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | J� est� nesse cargo.");

    new TypeCargo[15],
        Enviar[128];
    if(bMembro[id][idx][BaseCargo] < listitem) TypeCargo = "promovido(a)";
    else TypeCargo = "rebaixado(a)";

    format(Enviar, sizeof(Enviar), "UPDATE `basemembros` SET `Cargo` = %d WHERE `Nome` = '%s'", listitem, EscapeString(bMembro[id][idx][bNome]));
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao atualizar o cargo.");

    bMembro[id][idx][BaseCargo] = listitem;
    new pid = PegarIdPeloNick(bMembro[id][idx][bNome]);
    if(IsPlayerConnected(pid) && Jogador[pid][Logado] == true)
    {
        format(Enviar, sizeof(Enviar), "| BASE | Voc� foi %s para %s", TypeCargo, CargoBase(listitem));
        SendClientMessage(pid, 0xFFA500FF, Enviar);
    }

    format(Enviar, sizeof(Enviar), "| BASE | Voc� alterou o cargo do(a) %s para %s", bMembro[id][idx][bNome], CargoBase(listitem));
    SendClientMessage(playerid, 0xFFA500FF, Enviar);
    return 1;
}

Dialog:GerenciarMembro(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    new idx = GetPVarInt(playerid, "membroidx");
    if(bMembro[id][idx][TemMembro] == false) return 1;
    new Enviar[128];

    switch(listitem)
    {
        case 1:
        {
            if(!strcmp(bMembro[id][idx][bNome], PegarNick(playerid))) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode alterar seu cargo");
            if(perm != 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode alterar cargos");

            for(new i=0; i < 2; i++)
            {
                if(bMembro[id][idx][BaseCargo] == i) strcatEx(Enviar, "{CCCCCC}%s {FF4500}- Atual\n", CargoBase(i));
                else strcatEx(Enviar, "{CCCCCC}%s\n", CargoBase(i));
            }
            Dialog_Show(playerid, CargoMembro, DIALOG_STYLE_TABLIST, "{FFA500}Cargos", Enviar, "Alterar", "Fechar");
        }
        case 4:
        {
            if(!strcmp(bMembro[id][idx][bNome], PegarNick(playerid)) && perm == 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode se expulsar");
            else
            {
                if(strcmp(bMembro[id][idx][bNome], PegarNick(playerid))){
                    if(bMembro[id][idx][BaseCargo] >= perm && perm != 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode expulsar esse(a) membro(a)");
                }
            }
            
            format(Enviar, sizeof(Enviar), "DELETE FROM `basemembros` WHERE `Nome` = '%s'", EscapeString(bMembro[id][idx][bNome]));
            mysql_query(IDConexao, Enviar, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao expulsar esse(a) membro(a)");

            new pid = PegarIdPeloNick(bMembro[id][idx][bNome]);
            if(IsPlayerConnected(pid) && Jogador[pid][Logado] == true)
            {
                Jogador[pid][BaseID] = 0;
                format(Enviar, sizeof(Enviar), "| BASE | Voc� foi removido da base por %s", PegarNick(playerid));
                SendClientMessage(pid, 0xFFA500FF, Enviar);
            }
            format(Enviar, sizeof(Enviar), "| BASE | Voc� removeu o(a) membro(a) %s da sua base", bMembro[id][idx][bNome]);
            SendClientMessage(playerid, 0xFFA500FF, Enviar);
            new fdcs[MembroBase];
            bMembro[id][idx] = fdcs;
        }
    }
    return 1;
}

Dialog:ComprarBaseVeiculo(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        idx = GetPVarInt(playerid, "veiculoidx");
    if(vBase[id][idx][VeiculoModeloBase] != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | J� foi comprado um ve�culo para esse slot");

    new Enviar[128];

    if(BaseLoja[listitem][CoinX] == true){
        if(Jogador[playerid][Coins] < BaseLoja[listitem][PrecoX]) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem coins sucifiente.");
    }else{
        if(Jogador[playerid][Dinheiro] < BaseLoja[listitem][PrecoX]) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem dinheiro sucifiente.");
    }

    format(Enviar, sizeof(Enviar), "UPDATE `baseveiculos` SET `Modelo` = %d WHERE `BaseID` = %d AND `PosicaoID` = %d", BaseLoja[listitem][ModeloX], id, idx);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao comprar esse ve�culo");

    if(BaseLoja[listitem][CoinX] == true) Jogador[playerid][Coins] -= BaseLoja[listitem][PrecoX];
    else Jogador[playerid][Dinheiro] -= BaseLoja[listitem][PrecoX];

    vBase[id][idx][VeiculoModeloBase] = BaseLoja[listitem][ModeloX];
    vBase[id][idx][SlotDataBase] = true; 

    format(Enviar, sizeof(Enviar), "| BASE | Voc� comprou o ve�culo {FFA500}%s", GetVehicleNameByModel(BaseLoja[listitem][ModeloX]));
    SendClientMessage(playerid, -1, Enviar);
    return 1;
}

Dialog:VeiculoBaseCor1(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;    
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        idx = GetPVarInt(playerid, "veiculoidx");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar o ve�culo");
    
    new corXX;
    if(sscanf(inputtext, "d", corXX)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Cor inv�lida.");

    new Enviar[128];
    format(Enviar, sizeof(Enviar), "UPDATE `baseveiculos` SET `Cor1` = %d WHERE `BaseID` = %d AND `PosicaoID` = %d", corXX, id, idx);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao alterar a cor");

    vBase[id][idx][BaseCor1] = corXX;

    new ddf[2];
    GetVehicleColor(vBase[id][idx][VeiculoBaseID], ddf[0], ddf[1]);
    if(vBase[id][idx][VeiculoColocado] == true) ChangeVehicleColor(vBase[id][idx][VeiculoBaseID], corXX, ddf[1]);
    SendClientMessage(playerid, 0x00FF00FF, "| BASE | Ve�culo pintado com sucesso");
    return 1;
}

Dialog:VeiculoBaseCor2(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;    
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        idx = GetPVarInt(playerid, "veiculoidx");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar o ve�culo");
    
    new corXX;
    if(sscanf(inputtext, "d", corXX)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Cor inv�lida.");

    new Enviar[128];
    format(Enviar, sizeof(Enviar), "UPDATE `baseveiculos` SET `Cor2` = %d WHERE `BaseID` = %d AND `PosicaoID` = %d", corXX, id, idx);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao alterar a cor");

    vBase[id][idx][BaseCor2] = corXX;

    new ddf[2];
    GetVehicleColor(vBase[id][idx][VeiculoBaseID], ddf[0], ddf[1]);
    if(vBase[id][idx][VeiculoColocado] == true) ChangeVehicleColor(vBase[id][idx][VeiculoBaseID], ddf[0], corXX);
    SendClientMessage(playerid, 0x00FF00FF, "| BASE | Ve�culo pintado com sucesso");
    return 1;
}

Dialog:UpgradeVeiculoBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        idx = GetPVarInt(playerid, "veiculoidx");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar o ve�culo");
    if(vBase[id][idx][VeiculoColocado] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Ve�culo precisa estar desconectado.");
    if(vBase[id][idx][VeiculoModeloBase] == BaseLoja[listitem][ModeloX]) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse modelo j� est� sendo utilizado");

    new Enviar[128];
    if(BaseLoja[listitem][CoinX] == true){
        if(Jogador[playerid][Coins] < BaseLoja[listitem][PrecoX]) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem coins sucifiente.");
    }else{
        if(Jogador[playerid][Dinheiro] < BaseLoja[listitem][PrecoX]) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem dinheiro sucifiente.");
    }

    format(Enviar, sizeof(Enviar), "UPDATE `baseveiculos` SET `Modelo` = %d WHERE `BaseID` = %d AND `PosicaoID` = %d", BaseLoja[listitem][ModeloX], id, idx);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao comprar esse ve�culo");

    if(BaseLoja[listitem][CoinX] == true) Jogador[playerid][Coins] -= BaseLoja[listitem][PrecoX];
    else Jogador[playerid][Dinheiro] -= BaseLoja[listitem][PrecoX];
    vBase[id][idx][VeiculoModeloBase] = BaseLoja[listitem][ModeloX];

    format(Enviar, sizeof(Enviar), "| BASE | Voc� pagou {FFA500}$%s{FFFFFF} pela altera��o do ve�culo", DinheiroSeparar(BaseLoja[listitem][PrecoX]));
    SendClientMessage(playerid, -1, Enviar);
    return 1;
}

Dialog:ConfigurarBaseVeiculo(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        idx = GetPVarInt(playerid, "veiculoidx");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar o ve�culo");

    new Enviar[128];

    switch(listitem)
    {
        case 1:
        {
            new bool:Dsc = vBase[id][idx][VeiculoColocado];

            if(Dsc == false) Dsc = true;
            else Dsc = false;

            format(Enviar, sizeof(Enviar), "UPDATE `baseveiculos` SET `Conectado` = %d WHERE `BaseID` = %d AND `PosicaoID` = %d", Dsc, id, idx);
            mysql_query(IDConexao, Enviar, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao conectar o ve�culo");

            if(Dsc == false)
            {
                format(Enviar, sizeof(Enviar), "| BASE | Voc� desconectou o ve�culo %s", GetVehicleNameByModel(GetVehicleModel(vBase[id][idx][VeiculoBaseID])));
                DestroyVehicleEx(vBase[id][idx][VeiculoBaseID]);
                vBase[id][idx][VeiculoColocado] = false;
            }
            else
            {
                format(Enviar, sizeof(Enviar), "| BASE | Voc� conectou o ve�culo %s", GetVehicleNameByModel(GetVehicleModel(vBase[id][idx][VeiculoBaseID])));
                vBase[id][idx][VeiculoBaseID] = CreateVehicleEx(-1, vBase[id][idx][VeiculoModeloBase], vBase[id][idx][vBaseX], vBase[id][idx][vBaseY], vBase[id][idx][vBaseZ], vBase[id][idx][vBaseA], vBase[id][idx][BaseCor1], vBase[id][idx][BaseCor2], -1, 0);
                format(VeiculoServer[vBase[id][idx][VeiculoBaseID]][LocalVerificacao], 90, "BaseVeiculoVeric");
                vBase[id][idx][VeiculoColocado] = true;
            }
            SendClientMessage(playerid, 0xFFA500FF, Enviar);
        }
        case 2: Dialog_Show(playerid, VeiculoBaseCor1, DIALOG_STYLE_INPUT, "{FF0000}Ve�culo Base", "Coloque abaixo uma cor primaria de sua prefer�ncia", "Confirmar", "Cancelar");
        case 3: Dialog_Show(playerid, VeiculoBaseCor2, DIALOG_STYLE_INPUT, "{FF0000}Ve�culo Base", "Coloque abaixo uma cor secund�ria de sua prefer�ncia", "Confirmar", "Cancelar");
        case 4:
        {
            new Dialog[400];
            for(new d=0; d < sizeof(BaseLoja); d++)
            {
                if(BaseLoja[d][CoinX] == true) strcatEx(Dialog, "{CCCCCC}%s\t{FFFF00}$%s Coins\n", GetVehicleNameByModel(BaseLoja[d][ModeloX]), DinheiroSeparar(BaseLoja[d][PrecoX]));
                else strcatEx(Dialog, "{CCCCCC}%s\t{32CD32}$%s\n", GetVehicleNameByModel(BaseLoja[d][ModeloX]), DinheiroSeparar(BaseLoja[d][PrecoX]));
            }
            Dialog_Show(playerid, UpgradeVeiculoBase, DIALOG_STYLE_TABLIST, "{FF0000}Upgrades", Dialog, "Atualizar", "Fechar");
        }
    } 
    return 1;
}

Dialog:VeiculoBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar os ve�culos");

    new i = listitem,
        Dialog[400];
    
    if(vBase[id][i][SlotDataBase] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse slot n�o foi configurado pelo desenvolvedor.");
   
    SetPVarInt(playerid, "veiculoidx", i);
    if(vBase[id][i][VeiculoModeloBase] == 0) 
    {
        for(new d=0; d < sizeof(BaseLoja); d++)
        {
            if(BaseLoja[d][CoinX] == true) strcatEx(Dialog, "{FFA500}%s\t{FFFF00}$%s Coins\n", GetVehicleNameByModel(BaseLoja[d][ModeloX]), DinheiroSeparar(BaseLoja[d][PrecoX]));
            else strcatEx(Dialog, "{FFA500}%s\t{32CD32}$%s\n", GetVehicleNameByModel(BaseLoja[d][ModeloX]), DinheiroSeparar(BaseLoja[d][PrecoX]));
        }
        Dialog_Show(playerid, ComprarBaseVeiculo, DIALOG_STYLE_TABLIST, "{32CD32}Base Loja", Dialog, "Selecionar", "Fechar");
        return 1;
    }

    strcat(Dialog, "Op��o\tSobre\n");
    strcatEx(Dialog, "{FFFFFF}Modelo\t{FFA500}%s\n", GetVehicleNameByModel(vBase[id][i][VeiculoModeloBase]));
    if(vBase[id][i][VeiculoColocado] == false) strcat(Dialog, "{ff2d19}Desconectado\n");
    else strcat(Dialog, "{32CD32}Conectado\n");
    strcatEx(Dialog, "{FFFFFF}Cor Principal\t{FFA500}%d\n", vBase[id][i][BaseCor1]);
    strcatEx(Dialog, "{FFFFFF}Cor Secund�ria\t{FFA500}%d\n", vBase[id][i][BaseCor2]);
    strcat(Dialog, "{32CD32}Upgrade");
    Dialog_Show(playerid, ConfigurarBaseVeiculo, DIALOG_STYLE_TABLIST_HEADERS, "{FFA500}Configura��o", Dialog, "Selecionar", "Fechar");
    return 1;
}

Dialog:MembroBaseSelect(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new i = listitem;
    new perm;

    SetPVarInt(playerid, "membroidx", i);

    if(bMembro[id][i][TemMembro] == false)
    {
        perm = BasePermissao(id, PegarNick(playerid));
        if(perm == -1) return 1;
        if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para visualizar o(a) membro(a)");
        Dialog_Show(playerid, AdicionarMembroBase, DIALOG_STYLE_INPUT, "{FF0000}Adicionar", "Adicione o ID do usu�rio abaixo", "Confirmar", "Cancelar");
        return 1;
    }
    if(strcmp(bMembro[id][i][bNome], PegarNick(playerid)))
    {
        perm = BasePermissao(id, PegarNick(playerid));
        if(perm == -1) return 1;
        if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para visualizar o(a) membro(a)");   
    }

    new Dialog[260];
    strcatEx(Dialog, "{FFFFFF}Membro: {FFA500}%s\n", bMembro[id][i][bNome]);
    strcatEx(Dialog, "{FFFFFF}Cargo: {FFA500}%s\n", CargoBase(bMembro[id][i][BaseCargo]));
    strcatEx(Dialog, "{FFFFFF}Cofre: {32CD32}$%s\n", DinheiroSeparar(bMembro[id][i][BaseDeposito]));
    strcatEx(Dialog, "{FFFFFF}Entregas: {e2b960}%d\n", bMembro[id][i][BaseEntregas]);

    if(strcmp(bMembro[id][i][bNome], PegarNick(playerid))) strcat(Dialog, "{FF0000}Expulsar Membro");
    else strcat(Dialog, "{FF0000}Sair da Base");
    Dialog_Show(playerid, GerenciarMembro, DIALOG_STYLE_TABLIST, "{FFA500}Membro", Dialog, "Selecionar", "Fechar");
    return 1;
}

Dialog:ConfigCorTag(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(!IsHexNumber(inputtext)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa cor � inv�lida");
    if(strlen(inputtext) > 6 || strlen(inputtext) < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa cor � inv�lida");
    new CorFomar[70];
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    format(CorFomar, sizeof(CorFomar), "%sFF", inputtext);

    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "UPDATE `bases` SET `TagCor` = %d WHERE `Numero` = %d", HexToInt(CorFomar), id);
    mysql_query(IDConexao, Mensagem, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao alterar a cor da tag");
    Base[id][BaseTagCor] = HexToInt(CorFomar);
    format(Mensagem, sizeof(Mensagem), "| BASE | Voc� alterou a cor da tag base ( {%06x}%s{FFFFFF} )", StrToHex(IntToHex(Base[id][BaseTagCor])) >>> 8, Base[id][BaseTag]);
    SendClientMessage(playerid, -1, Mensagem);
    return 1;
}

Dialog:ConfigNomeTag(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) > 6) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | M�ximo de caracteres � 6");
    if(strlen(inputtext) < 3) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | m�nimo de 3 caracteres");
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "UPDATE `bases` SET `Tag` = '%s' WHERE `Numero` = %d", EscapeString(inputtext), id);
    mysql_query(IDConexao, Mensagem, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao alterar a tag");
    format(Base[id][BaseTag], 10, inputtext);
    format(Mensagem, sizeof(Mensagem), "| BASE | Voc� alterou a TAG base para %s", inputtext);
    SendClientMessage(playerid, -1, Mensagem);
    AtualizarBase(id);
    return 1;
}

Dialog:ConfigNomeBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) > 24) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | M�ximo de caracteres � 24");
    if(Jogador[playerid][Coins] < 7000) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem $7.000 coins");
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "UPDATE `bases` SET `Nome` = '%s' WHERE `Numero` = %d", EscapeString(inputtext), id);
    mysql_query(IDConexao, Mensagem, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao alterar o nome");
    Jogador[playerid][Coins] -= 7000;
    format(Base[id][BaseNome], 30, inputtext);
    format(Mensagem, sizeof(Mensagem), "| BASE | Voc� alterou o nome da base para %s", inputtext);
    SendClientMessage(playerid, -1, Mensagem);
    AtualizarBase(id);
    return 1;
}

Dialog:TagConfigMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem)
    {
        case 0: Dialog_Show(playerid, ConfigCorTag, DIALOG_STYLE_INPUT, "{FF0000}Tag", "Coloque abaixo uma cor em hexadecimal para a tag", "Confirmar", "Fechar");
        case 1: Dialog_Show(playerid, ConfigNomeTag, DIALOG_STYLE_INPUT, "{FF0000}Tag Nome", "Coloque abaixo o nome da TAG base", "Confirmar", "Fechar");
        case 2: Dialog_Show(playerid, ConfigNomeBase, DIALOG_STYLE_INPUT, "{FF0000}Nome Base", "Voc� gastar� $7.000 coins para alterar o nome da base\nColoque abaixo o nome que deseja", "Confirmar", "Fechar");
    }
    return 1;
}

Dialog:ConfiguracaoBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar a base");

    new Enviar[128];
    switch(listitem)
    {
        case 0:
        {
            new bool:dca = Base[id][BaseInvasao];
            if(dca == false) dca = true;
            else dca = false;
            format(Enviar, sizeof(Enviar), "UPDATE `bases` SET `Invasao` = %d WHERE `Numero` = %d", dca, id);
            mysql_query(IDConexao, Enviar, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao mudar o status da invas�o");

            if(dca == true) AbrirPortaoBase(id, false);
            else AbrirPortaoBase(id, true, 500);

            Base[id][BaseInvasao] = dca;
            SendClientMessage(playerid, 0xFFA500FF, "| BASE | Voc� mudou o status da invas�o da base");
            AtualizarInfoBase(id);
        }
        case 1:
        {
            new bool:dca = Base[id][BaseDM];
            if(dca == false) dca = true;
            else dca = false;
            format(Enviar, sizeof(Enviar), "UPDATE `bases` SET `DM` = %d WHERE `Numero` = %d", dca, id);
            mysql_query(IDConexao, Enviar, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um erro ao mudar o status do deathmatch");
            
            if(dca == true) AbrirPortaoBase(id, false);
            else AbrirPortaoBase(id, true, 500);

            Base[id][BaseDM] = dca;
            SendClientMessage(playerid, 0xFFA500FF, "| BASE | Voc� mudou o status do deathmatch da base");
            AtualizarInfoBase(id);  
        }
        case 2:
        {
            if(Base[id][BaseArma] == true) Base[id][BaseArma] = false;
            else Base[id][BaseArma] = true;
            SendClientMessage(playerid, 0xFFA500FF, "| BASE | Voc� mudou o status de arma free da base");
            AtualizarInfoBase(id);     
        }
        case 3:
        {
            if(perm != 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para acessar essa �rea");
            new Dialog[128];
            strcat(Dialog, "Op��o\tSobre\n");
            strcatEx(Dialog, "Alterar Cor\t{%06x}Exemplo\n", StrToHex(IntToHex(Base[id][BaseTagCor])) >>> 8);
            strcatEx(Dialog, "Mudar Tag\t{FFA500}%s\n", Base[id][BaseTag]);
            strcatEx(Dialog, "Mudar Nome\t{FFA500}%s", Base[id][BaseNome]);
            Dialog_Show(playerid, TagConfigMenu, DIALOG_STYLE_TABLIST_HEADERS, "{FFA500}Configura��o Tag", Dialog, "Selecionar", "Fechar");
        }
    }
    return 1;
}

Dialog:RenovarBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        Enviar[128];

    new Simulado = Base[id][BaseVencimento];
    Simulado -= Base[id][BaseDesconto];
    Simulado += (Base[id][BaseVencimento] > 0 ? (30 * 86400) : (gettime() + (30 * 86400)));
    format(Enviar, sizeof(Enviar), "UPDATE `bases` SET `Vencimento` = %d WHERE `Numero` = %d", Simulado, id);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao renovar.");

    new dda = Base[id][BaseCoins];
    dda -= 5000;
    dda -= Base[id][BaseDesconto];
    Jogador[playerid][Coins] -= dda;
    Base[id][BaseVencimento] = Simulado;
    format(Enviar, sizeof(Enviar), "| BASE | Voc� pagou $%s pela renova��o da base ( Vencimento: %s )", DinheiroSeparar(dda), GetDateFromTimeExx(Base[id][BaseVencimento]));
    SendClientMessage(playerid, 0xFFA500FF, Enviar);
    return 1;
}

Dialog:VenderBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    SqlRemoverBase(id);
    LimparBaseInfo(id);
    AtualizarBase(id);
    SendClientMessage(playerid, 0xFFA500FF, "| BASE | Voc� vendeu sua base para o servidor");
    return 1;
}

Dialog:BaseInformacao(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar essa �rea");
    
    switch(listitem)
    {
        case 0:
        {
            //if(!PrecisaRenovar(id, 3)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� ainda n�o pode renovar sua base.");
            if(perm < 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar essa �rea");
            if(Base[id][BloquearRenovacao] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Sua base foi bloqueado.");
            new Mensagem[128];
            new asd = Base[id][BaseCoins];
            asd -= 5000;
            asd -= Base[id][BaseDesconto];
            if(Jogador[playerid][Coins] < asd){
                format(Mensagem, sizeof(Mensagem), "| ERRO | Voc� n�o tem $%s coins para renovar", DinheiroSeparar(asd));
                SendClientMessage(playerid, 0xFF4500FF, Mensagem);
                return 1;
            }
            format(Mensagem, sizeof(Mensagem), "Voc� vai gastar $%s de coins para renovar a base por 30 dias, deseja continuar?", DinheiroSeparar(asd));
            Dialog_Show(playerid, RenovarBase, DIALOG_STYLE_MSGBOX, "{FFA500}Renovar Base", Mensagem, "Confirmar", "Fechar");

        }
        case 1: Dialog_Show(playerid, RecrutamentoBase, DIALOG_STYLE_INPUT, "{FFA500}Recrutamento", "Coloque abaixo uma mensagem para o recrutamento", "Confirmar", "Fechar");
        case 2:
        {
            if(perm < 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para gerenciar essa �rea");
            Dialog_Show(playerid, VenderBase, DIALOG_STYLE_MSGBOX, "{FFA500}Base", "Voc� realmente deseja liberar sua base para o servidor?\nObs: Esse processo n�o tem volta, sua base ser� liberada para o servidor\nDeseja continuar?", "Continuar", "Fechar");
        }
    }
    return 1;
}

Dialog:RecrutamentoBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) > 128) return 1;

    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");

    new Mensagem[1500];
    if(Base[id][BaseAnunciar] > gettime()){
        format(Mensagem, sizeof(Mensagem), "| ERRO | Voc� n�o pode anunciar em %s", ConverterSegundosEx(Base[id][BaseAnunciar]-gettime()));
        SendClientMessage(playerid, 0xFF4500FF, Mensagem);
        return 1;
    }  

    new Enviar[90],
        idaa = gettime()+10800;
    format(Enviar, sizeof(Enviar), "UPDATE `bases` SET `BaseAnunciar` = %d WHERE `Numero` = %d", idaa, id);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao fazer o recrutamento");

    Base[id][BaseAnunciar] = idaa;

    stringclear(Mensagem);
    format(Mensagem, sizeof(Mensagem), "| RECRUTAMENTO | O(A) %s %s abriu recrutamento para %s", CargoBase(bMembro[id][PosicaoBase(id, PegarNick(playerid))][BaseCargo]), PegarNick(playerid), Base[id][BaseNome]);
    SendClientMessageToAll(0xffb800FF, Mensagem);
    return 1;
}

Dialog:BaseCofreConfig(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;

    switch(listitem)
    {
        case 0:
        {
            new Dialog[90];
            strcat(Dialog, "Retirar Dinheiro\n");
            strcat(Dialog, "Depositar Dinheiro");
            Dialog_Show(playerid, BaseCofreOpcao, DIALOG_STYLE_TABLIST, "{FFA500}Cofre", Dialog, "Selecionar", "Fechar");
        }
    }
    return 1;
}

Dialog:BaseCofreOpcao(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;

    switch(listitem)
    {
        case 0:
        {
            if(perm < 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para acessar essa �rea");   
            Dialog_Show(playerid, ConfirmarCofreBase, DIALOG_STYLE_MSGBOX, "{FF0000}Confirma��o", "Voc� realmente deseja sacar?", "Confirmar", "Fechar");
        }
        case 1:
        {
            Dialog_Show(playerid, DepositarBase, DIALOG_STYLE_INPUT, "{FF0000}Base", "Coloque abaixo o valor que voc� deseja depositar", "Confirmar", "Fechar");  
        }
    }

    return 1;
}

Dialog:ConfirmarCofreBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        Enviar[128];
    if(Base[id][BaseCofre] < 2000) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode sacar ainda");
    format(Enviar, sizeof(Enviar), "UPDATE `bases` SET `Cofre` = 0 WHERE `Numero` = %d", id);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema na retirada do dinheiro");

    new aasd = Base[id][BaseCofre];
    Jogador[playerid][Dinheiro] += Base[id][BaseCofre];
    Base[id][BaseCofre] -= aasd;

    format(Enviar, sizeof(Enviar), "| BASE | Voc� retirou {32CD32}$%s{FFFFFF} do cofre da base", DinheiroSeparar(aasd));
    SendClientMessage(playerid, -1, Enviar);
    return 1;
}

Dialog:DepositarBase(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;

    if(pTempo[playerid][TransferirBanco] > gettime()){
        new hjh[128];
        format(hjh, sizeof(hjh), "| ERRO | Voc� precisa aguardar %s antes de depositar", ConverterSegundos(pTempo[playerid][TransferirBanco]));
        SendClientMessage(playerid, 0xFF4500FF, hjh);
        return 1;
    }

    new vlr;
    if(sscanf(inputtext, "d", vlr)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | N�mero Inv�lido");
    if(vlr > 500000) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� s� pode colocar $500.000");
    if(vlr < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� s� pode colocar esse valor");
    if(Jogador[playerid][Dinheiro] < vlr) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem toda essa quantia");

    new id = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        idx,
        Enviar[300];
    idx = PosicaoBase(id, PegarNick(playerid));
    new SimBase = Base[id][BaseCofre],
        SimMembro = bMembro[id][idx][BaseDeposito];
    SimBase += vlr;
    SimMembro += vlr;

    strcatEx(Enviar, "UPDATE `bases` SET `Cofre` = %d WHERE `Numero` = %d; ", SimBase, id);
    strcatEx(Enviar, "UPDATE `basemembros` SET `Deposito` = %d WHERE `BaseID` = %d AND `PosicaoID` = %d", SimMembro, id, idx);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Houve um problema ao depositar dinheiro");

    Jogador[playerid][Dinheiro] -= vlr;
    Base[id][BaseCofre] = SimBase;
    bMembro[id][idx][BaseDeposito] += SimMembro;
    format(Enviar, sizeof(Enviar), "| BASE | Voc� depositou {32CD32}$%s{FFFFFF} no cofre base", DinheiroSeparar(vlr));
    SendClientMessage(playerid, -1, Enviar);
    return 1;
}

Dialog:BaseMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new id = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new perm = BasePermissao(id, PegarNick(playerid));
    if(perm == -1) return 1;
    new Dialog[2500];

    switch(listitem)
    {
        case 0:
        {
            // if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para acessar as configura��es");
            strcat(Dialog, "Op��o\tAdicional\n");
            strcatEx(Dialog, "Cofre\t{B22222}R$%s\n", DinheiroSeparar(Base[id][BaseCofre]));
            strcatEx(Dialog, "Entregas\t{e2b960}%d", Base[id][BaseEntregasGeral]);
            Dialog_Show(playerid, BaseCofreConfig, DIALOG_STYLE_TABLIST_HEADERS, "{FFA500}Cofre", Dialog, "Selecionar", "Fechar");
        }
        case 1:
        {
            strcat(Dialog, "Slot\tMembro\tCargo\n");
            for(new i=0; i < MAX_MEMBROS; i++)
            {
                if(bMembro[id][i][TemMembro] == false) strcatEx(Dialog, "{CCCCCC}%d.\t{00BFFF}N/A\t{FFA500}N/A\n", i+1);
                else strcatEx(Dialog, "{CCCCCC}%d.\t{00BFFF}%s\t{FFA500}%s\n", i+1, bMembro[id][i][bNome], CargoBase(bMembro[id][i][BaseCargo]));
            }
            Dialog_Show(playerid, MembroBaseSelect, DIALOG_STYLE_TABLIST_HEADERS, "{FFA500}Membros da Base", Dialog, "Selecionar", "Fechar");
        }
        case 2:
        {
            strcat(Dialog, "Op��o\tAdicional\n");
            if(!PrecisaRenovar(id, 3)) strcatEx(Dialog, "Vencimento\t{FFA500}%s\n", GetDateFromTimeExx(Base[id][BaseVencimento]));
            else strcatEx(Dialog, "Vencimento\t{FFA500}%s </Renovar>\n", GetDateFromTimeExx(Base[id][BaseVencimento]));
            
            if(Base[id][BaseAnunciar] > gettime()) strcatEx(Dialog, "Anunciar Recrutamento\t{FFA500}%s\n", ConverterSegundosEx(Base[id][BaseAnunciar]-gettime()));
            else strcat(Dialog, "Anunciar Recrutamento\t{FFA500}Anunciar\n");

            strcat(Dialog, "{32CD32}Liberar para o Servidor");
            Dialog_Show(playerid, BaseInformacao, DIALOG_STYLE_TABLIST_HEADERS, "{FFA500}Informa��es", Dialog, "Selecionar", "Fechar");
        }
        case 3:
        {
            strcat(Dialog, "Slot\tModelo\tEstado\n");
            for(new i=0; i < MAX_BASEVEH; i++)
            {
                if(vBase[id][i][SlotDataBase] == false) strcatEx(Dialog, "{FF0000}%d\t{CCCCCC}Esperando Configura��o\n", i+1);
                else if(vBase[id][i][VeiculoModeloBase] == 0) strcatEx(Dialog, "{FF0000}%d\t{CCCCCC}N�o Comprado\n", i+1);
                else if(vBase[id][i][VeiculoColocado] == false) strcatEx(Dialog, "{CCCCCC}%d\t{FFA500}%s\t{ff2d19}Desconectado\n", i+1, GetVehicleNameByModel(vBase[id][i][VeiculoModeloBase]));
                else strcatEx(Dialog, "{CCCCCC}%d\t{FFA500}%s\t{32CD32}Conectado\n", i+1, GetVehicleNameByModel(vBase[id][i][VeiculoModeloBase]));
            }
            Dialog_Show(playerid, VeiculoBase, DIALOG_STYLE_TABLIST_HEADERS, "{FFA500}Ve�culos Base", Dialog, "Selecionar", "Fechar");
        }
        case 4:
        {
            if(perm < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para acessar as configura��es");
            strcat(Dialog, "Op��o\tSobre\n");
            strcatEx(Dialog, "{FFFFFF}Invas�o\t%s\n", StatusInvasao(id));
            strcatEx(Dialog, "{FFFFFF}DeathMatch\t%s\n", StatusDM(id));
            strcatEx(Dialog, "{FFFFFF}Armas Free\t%s\n", StatusArmas(id));
            strcatEx(Dialog, "{FFFFFF}Configurar Tag\t%s\n", Base[id][BaseTag]);
            strcatEx(Dialog, "{FFFFFF}Permiss�o Entrada\t%s\n", TrancaBase(id));
            if(strcmp(Base[id][BaseSenha], "*")) strcatEx(Dialog, "{FFFFFF}Senha\t{FFA500}%s", Base[id][BaseSenha]);
            Dialog_Show(playerid, ConfiguracaoBase, DIALOG_STYLE_TABLIST_HEADERS, "{FFA500}Configura��o", Dialog, "Selecionar", "Fechar");
        }
    }
    return 1;
}

CMD:menubase(playerid)
{
    new Dialog[148],
        id = GetPVarInt(playerid, "InteriorPersonalizadoID");

    if(Jogador[playerid][uInteriorEx] != 9) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� em uma base");
    if(BasePermissao(id, PegarNick(playerid)) == -1 && Jogador[playerid][Admin] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");

    strcat(Dialog, "Op��o\tSobre\n");
    strcatEx(Dialog, "Cofre\t{32CD32}$%s\n", DinheiroSeparar(Base[id][BaseCofre]));
    strcatEx(Dialog, "Membros\t{FFA500}%d/%d\n", MembrosBase(id), MAX_MEMBROS);
    strcat(Dialog, "Informa��es\n");
    strcatEx(Dialog, "Ve�culos\t{FFA500}%d/%d\n", VeiculosBase(id), MAX_BASEVEH);
    strcat(Dialog, "Configura��es");
    Dialog_Show(playerid, BaseMenu, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}Base", Dialog, "Selecionar", "Fechar");
    return 1;
}