Dialog:SenhaEntrarCasa(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;

    for(new i=0; i < MAX_CASAS; i++)
    {
        if(pCasa[i][Colocado] == false) continue;
        if(!IsPlayerInRangeOfPoint(playerid, 3.0, pCasa[i][cPosicaoX], pCasa[i][cPosicaoY], pCasa[i][cPosicaoZ])) continue;
        if(isnull(pCasa[i][cSenha])) return 1;
        if(strcmp(pCasa[i][cSenha], inputtext)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Senha incorreta!");
        EntrarCasa(playerid, i);
        break;
    } 
    return 0;
} 

Dialog:ColocarSenhaCasa(playerid, response, listitem, inputtext[]) 
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) < 2) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Senha muito curta");
    if(strlen(inputtext) > 24) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Senha muito grande");
    if(CaracterEspecial(inputtext)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar caracteres especiais!");

    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new Enviar[90];
    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Tranca` = 1, `Senha` = '%s' WHERE `Numero` = %d", EscapeString(inputtext), casaid);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Ocorreu um problema ao alterar sua casa!");
    new Mensagem[90];
    format(Mensagem, sizeof(Mensagem), "| CASA | Voc� alterou a senha da sua casa ( %s )", inputtext);
    SendClientMessage(playerid, -1, Mensagem);
    pCasa[casaid][cTranca] = 1;
    format(pCasa[casaid][cSenha], 90, inputtext);
    AtualizarCasa(casaid);
    return 0;
}

Dialog:TrancaCasa(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID");
    if(pCasa[casaid][cTranca] == listitem) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Sua casa j� est� com essa permiss�o");
    
    if(listitem == 1){
        Dialog_Show(playerid, ColocarSenhaCasa, DIALOG_STYLE_INPUT, "{FF0000}Senha", "Coloque uma senha abaixo", "Confirmar", "Cancelar");
        return 1;
    }

    new Enviar[90];
    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Tranca` = %d WHERE `Numero` = %d", listitem, casaid);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Ocorreu um problema ao alterar sua casa!");
    new Mensagem[90];
    format(Mensagem, sizeof(Mensagem), "| CASA | Voc� alterou sua casa para %s{FFFFFF} sua casa", PegarCasaStatus(listitem));
    SendClientMessage(playerid, -1, Mensagem);
    pCasa[casaid][cTranca] = listitem;
    AtualizarCasa(casaid);
    return 0;
}

Dialog:MensagemCasa(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID");
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) < 2) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Mensagem muito curta");
    if(strlen(inputtext) > 35) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Mensagem muito grande");
    if(CaracterEspecial(inputtext)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar caracteres especiais!");

    new Enviar[128];
    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Mensagem` = '%s' WHERE `Numero` = %d", EscapeString(inputtext), casaid);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Ocorreu um problema ao alterar sua casa!");
    format(pCasa[casaid][cMensagem], 90, inputtext);
    format(Enviar, sizeof(Enviar), "| CASA | Voc� alterou o nome da sua casa para {00BFFF}%s", inputtext);
    SendClientMessage(playerid, -1, Enviar);
    AtualizarCasa(casaid);
    return 1;
}

Dialog:MoradorAdicionar(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new id;
    if(sscanf(inputtext, "d", id)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Coloque o ID do(a) novo(a) morador(a)");
    if(id == playerid) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o pode se adicionar");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Jogador(a) n�o encontrado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Jogador(a) n�o efetuou login");

    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        iid = pCasa[casaid][cInterior],
        vw = casaid,
        Enviar[128];

    vw++;
    vw = (vw*vw);
    iid -= 1;

    if(GetPlayerVirtualWorld(id) != vw && Jogador[id][uInteriorEx] != 1 && GetPlayerInterior(id) != pInterior[iid][Interior]) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Jogador(a) n�o est� na sua casa");
    if(!IsPlayerInRangeOfPoint(id, 3.0, pInterior[iid][cInterX], pInterior[iid][cInterY], pInterior[iid][cInterZ])) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Jogador(a) n�o est� perto da porta");
    new listaah = GetPVarInt(playerid, "MoradorID");
    if(strcmp(pMorador[casaid][listaah][Morador], "*")) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | J� existe um morador");
    if(id == playerid) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o pode se adicionar!");
    if(VerificarSeTemCasa(id)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Esse jogador(a) j� est� morando em uma casa");

    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Morador%d` = '%s' WHERE `Numero` = %d", listaah, EscapeString(PegarNick(id)), casaid);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Ocorreu um problema ao adicionar esse morador!");  
    format(Enviar, sizeof(Enviar), "| CASA | Voc� agora est� morando na casa do(a) %s", PegarNick(playerid));
    SendClientMessage(id, 0xFFFF00FF, Enviar);
    format(Enviar, sizeof(Enviar), "| CASA | %s agora est� morando na sua casa", PegarNick(id));
    SendClientMessage(playerid, 0xFFFF00FF, Enviar);
    format(pMorador[casaid][listaah][Morador], 90, PegarNick(id));
    return 0;
}

Dialog:OpcaoMorador(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new lid = GetPVarInt(playerid, "MoradorID");
    if(strcmp(pMorador[casaid][lid][Morador], "*"))
    {
        new Enviar[90];
        format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Morador%d` = '*' WHERE `Numero` = %d", lid, casaid);
        mysql_query(IDConexao, Enviar, false);
        if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Ocorreu um problema ao remover esse morador!");
        if(!strcmp(PegarNick(playerid), pCasa[casaid][cDono]))
        {
            if(IsPlayerConnected(PegarIdPeloNick(pMorador[casaid][lid][Morador])))
            {
                format(Enviar, sizeof(Enviar), "| CASA | Voc� foi removido(a) da casa %d por %s", casaid, PegarNick(playerid));
                SendClientMessage(PegarIdPeloNick(pMorador[casaid][lid][Morador]), 0xFFFF00FF, Enviar);
            }
            format(Enviar, sizeof(Enviar), "| CASA | Voc� removeu a moradia do(a) %s", pMorador[casaid][lid][Morador]);
            SendClientMessage(playerid, 0xFFFF00FF, Enviar);
        }
        else SendClientMessage(playerid, 0xFFFF00FF, "| CASA | Voc� removeu sua moradia!");   
        format(pMorador[casaid][lid][Morador], 90, "*");
        AtualizarCasa(casaid);
        return 1;
    }
    else if(strcmp(PegarNick(playerid), pCasa[casaid][cDono])) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem permiss�o");
    Dialog_Show(playerid, MoradorAdicionar, DIALOG_STYLE_INPUT, "{FF0000}Morador", "Coloque o ID do(a) novo(a) morador(a) abaixo", "Confirmar", "Fechar");
    return 0;
}

Dialog:MoradorCasa(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        Dialog[90];
    //if(strcmp(PegarNick(playerid), pCasa[casaid][cDono])) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem permiss�o");
    
    if(!strcmp(pMorador[casaid][listitem][Morador], PegarNick(playerid))) strcat(Dialog, "Remover ( Sair )\n");
    else if(strcmp(pMorador[casaid][listitem][Morador], "*") && strcmp(pMorador[casaid][listitem][Morador], PegarNick(playerid))) strcat(Dialog, "Remover Morador(a)\n");
    else strcat(Dialog, "Adicionar Morador(a)\n");
    SetPVarInt(playerid, "MoradorID", listitem);
    Dialog_Show(playerid, OpcaoMorador, DIALOG_STYLE_TABLIST, "{FF0000}Menu Morador", Dialog, "Selecionar", "Fechar");
    return 0;
}

Dialog:UparCasa(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID");

    /*if(pCasa[casaid][cPreco] > 0 && pCasa[casaid][cCoins] < 1) SetPVarInt(playerid, "MultiPlicacacoaDaCasa", pCasa[casaid][cPreco]);
    else if(pCasa[casaid][cPreco] < 1 && pCasa[casaid][cCoins] > 0) SetPVarInt(playerid, "MultiPlicacacoaDaCasa", (pCasa[casaid][cCoins]+250000));
    else SetPVarInt(playerid, "MultiPlicacacoaDaCasa", (pCasa[casaid][cCoins] + pCasa[casaid][cPreco]));

    new InteriorFinal,
        ValorReal,
        OutroValor,
        UpSelecionado = 0;

    for(new i=1; i < pCasa[casaid][cInteriorMax]+1; i++)
    {
        if(i > pCasa[casaid][cInterior])
        {
            if(UpSelecionado != listitem){
                UpSelecionado++;
                continue;
            }  
            new Cambiarra = UpSelecionado += 1;
            OutroValor = GetPVarInt(playerid, "MultiPlicacacoaDaCasa");
            ValorReal = OutroValor*Cambiarra;
            InteriorFinal = i;
            break;
        }
    }*/

    new InteriorFinal,
        ValorReal;
    InteriorUpgrade(playerid, casaid, listitem, InteriorFinal, ValorReal);

    if(pCasa[casaid][cInterior] > 1 && InteriorFinal <= pCasa[casaid][cInterior]) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o pode selecionar esse interior!");
    if(Jogador[playerid][Dinheiro] < ValorReal) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem dinheiro sucifiente!");

    new Enviar[128];
    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Interior` = %d WHERE `Numero` = %d", InteriorFinal, casaid);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Ocorreu um problema ao upar sua casa, solicite um desenvolvedor para resolver!");
    Jogador[playerid][Dinheiro] -= ValorReal;
    // new AntigoIntt = pCasa[casaid][cInterior];
    pCasa[casaid][cInterior] = InteriorFinal;
    format(Enviar, sizeof(Enviar), "| CASA | Voc� gastou {00FF00}$%s{FFFFFF} com o upgrade {00BFFF}%d", DinheiroSeparar(ValorReal), InteriorFinal);
    SendClientMessage(playerid, -1, Enviar);
    format(Enviar, sizeof(Enviar), "| CASA | O(A) Jogador(a) {00BFFF}%s[%d]{FFFFFF} upou essa casa para o interior {00BFFF}%d", PegarNick(playerid), playerid, InteriorFinal);

    new EstaIn = pCasa[casaid][cInterior];
    EstaIn -= 1;

    //Configuracoes
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i) && Jogador[i][Logado] == false) continue;
        if(GetPVarInt(i, "InteriorPersonalizadoID") != casaid || Jogador[i][uInteriorEx] != 1) continue;

        SetPlayerInterior(i, pInterior[EstaIn][Interior]);
        SetPlayerPos(i, pInterior[EstaIn][cInterX], pInterior[EstaIn][cInterY], pInterior[EstaIn][cInterZ]);
        SetPlayerFacingAngle(i, pInterior[EstaIn][cInterA]);
        if(i != playerid) SendClientMessage(i, -1, Enviar);
    }

    DesativarMoveis(casaid);
    AtualizarCasa(casaid); 
    return 0;
}

Dialog:VendaPreco(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new PrecoJ;
    if(sscanf(inputtext, "d", PrecoJ)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Pre�o inv�lido!");
    if(PrecoJ < 5000) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� precisa colocar um valor maior que $5.000");
    if(PrecoJ > 60000000) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� precisa ser menor que $60.000.000");

    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        Enviar[128];
    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `JPreco` = %d WHERE `Numero` = %d", PrecoJ, casaid);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Houve um problema ao atualizar sua casa");
    pCasa[casaid][cJPreco] = PrecoJ;
    AtualizarCasa(casaid);
    return 0;
}

Dialog:VendaEscolha(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem)
    {
        case 0: Dialog_Show(playerid, ConfirmarVendaCasa, DIALOG_STYLE_INPUT, "{FF0000}Confirma��o", "Coloque abaixo o c�digo da sua conta para confimar", "Selecionar", "Fechar");   
        case 1: Dialog_Show(playerid, VendaPreco, DIALOG_STYLE_INPUT, "{00FF00}Venda", "Coloque abaixo o pre�o que voc� est� pedindo", "Selecionar", "Fechar");   
        case 2:
        {
            new Enviar[128],
                casaid = GetPVarInt(playerid, "InteriorPersonalizadoID");
            format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `JPreco` = 0 WHERE `Numero` = %d", casaid);
            mysql_query(IDConexao, Enviar, false);
    
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Houve um problema ao atualizar sua casa");
            pCasa[casaid][cJPreco] = 0;
            AtualizarCasa(casaid);
        }
    }
    return 0;
}

Dialog:MenuCasa(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID");
    new Dialog[1200];
    switch(listitem)
    {
        case 0:
        {
            if(strcmp(PegarNick(playerid), pCasa[casaid][cDono])) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem permiss�o");
            strcat(Dialog, "Destrancar\n");
            strcat(Dialog, "Trancar com Senha\n");
            strcat(Dialog, "Trancar");
            Dialog_Show(playerid, TrancaCasa, DIALOG_STYLE_TABLIST, "{FF0000}Tranca", Dialog, "Selecionar", "Fechar");
        }
        case 1:
        {
            if(strcmp(PegarNick(playerid), pCasa[casaid][cDono])) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem permiss�o");
            Dialog_Show(playerid, MensagemCasa, DIALOG_STYLE_INPUT, "{FF0000}Mensagem", "Altere a mensagem da sua casa", "Selecionar", "Fechar");
        }
        case 2:
        {
            if(pCasa[casaid][LixoD] < 1) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem lixo dentro de casa");
            
            new Enviar[128],
                LixoFEx = pCasa[casaid][LixoF],
                LixoDEx = pCasa[casaid][LixoD]
            ;
            LixoFEx += LixoDEx;
            format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `LixoF`=%d, `LixoD`=0 WHERE `Numero`=%d", LixoFEx, casaid);
            mysql_query(IDConexao, Enviar, false);
            if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Houve um problema ao remover o lixo, entre em contato com um desenvolvedor");
            pCasa[casaid][LixoF] = LixoFEx;
            pCasa[casaid][LixoD] = 0;
            SendClientMessage(playerid, 0xFFFF00FF, "| CASA | Voc� retirou o(s) lixo(s) de dentro de casa");
            AtualizarCasa(casaid);
        }
        case 3:
        {
            if(pCasa[casaid][cInterior] < 3) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Essa casa precisa ser level 3 para suportar moradores");
            strcat(Dialog, "Lista\tNome\n");
            if(pCasa[casaid][cInterior] >= 3){
                if(strcmp(pMorador[casaid][0][Morador], "*")) strcatEx(Dialog, "1. Morador(a)\t{fc520f}%s\n", pMorador[casaid][0][Morador]);
                else strcat(Dialog, "1. Morador(a)\t{FF0000}N/A\n");  
            }
            if(pCasa[casaid][cInterior] >= 5){
                if(strcmp(pMorador[casaid][1][Morador], "*")) strcatEx(Dialog, "2. Morador(a)\t{fc520f}%s\n", pMorador[casaid][1][Morador]);
                else strcat(Dialog, "2. Morador(a)\t{FF0000}N/A\n");
            }
            if(pCasa[casaid][cInterior] >= 10){
                if(strcmp(pMorador[casaid][2][Morador], "*")) strcatEx(Dialog, "3. Morador(a)\t{fc520f}%s\n", pMorador[casaid][2][Morador]);
                else strcat(Dialog, "3. Morador(a)\t{FF0000}N/A\n");
            }
            if(pCasa[casaid][cInterior] >= 13){
                if(strcmp(pMorador[casaid][3][Morador], "*")) strcatEx(Dialog, "4. Morador(a)\t{fc520f}%s\n", pMorador[casaid][3][Morador]);
                else strcat(Dialog, "4. Morador(a)\t{FF0000}N/A\n");
            }
            if(pCasa[casaid][cInterior] >= 14){
                if(strcmp(pMorador[casaid][4][Morador], "*")) strcatEx(Dialog, "5. Morador(a)\t{fc520f}%s\n", pMorador[casaid][4][Morador]);
                else strcat(Dialog, "5. Morador(a)\t{FF0000}N/A\n");
            }
            if(pCasa[casaid][cInterior] >= 18){
                if(strcmp(pMorador[casaid][5][Morador], "*")) strcatEx(Dialog, "6. Morador(a)\t{fc520f}%s\n", pMorador[casaid][5][Morador]);
                else strcat(Dialog, "6. Morador(a)\t{FF0000}N/A\n");
            }
            Dialog_Show(playerid, MoradorCasa, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}Moradores(as)", Dialog, "Selecionar", "Fechar");
        }
        case 4:
        {
            if(strcmp(PegarNick(playerid), pCasa[casaid][cDono])) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem permiss�o");
            new OutroValor,
                ValorGeral,
                ContageeemM = 1;
            
            if(pCasa[casaid][cPreco] > 0 && pCasa[casaid][cCoins] < 1) SetPVarInt(playerid, "MultiPlicacacoaDaCasa", pCasa[casaid][cPreco]);
            else if(pCasa[casaid][cPreco] < 1 && pCasa[casaid][cCoins] > 0) SetPVarInt(playerid, "MultiPlicacacoaDaCasa", (pCasa[casaid][cCoins]+250000));
            else SetPVarInt(playerid, "MultiPlicacacoaDaCasa", (pCasa[casaid][cCoins] + pCasa[casaid][cPreco]));
            
            strcat(Dialog, "Upgrade\tPre�o\n");
            for(new i=1; i < pCasa[casaid][cInteriorMax]+1; i++)
            {
                if(i > pCasa[casaid][cInterior])
                {
                    OutroValor = GetPVarInt(playerid, "MultiPlicacacoaDaCasa");
                    ValorGeral = OutroValor*ContageeemM;       

                    if(ValorGeral < Jogador[playerid][Dinheiro]) strcatEx(Dialog, "{1E90FF}Interior %d\t{32CD32}$%s\n", i, DinheiroSeparar(ValorGeral));
                    else strcatEx(Dialog, "{1E90FF}Interior %d\t{FF0000}$%s\n", i, DinheiroSeparar(ValorGeral));
                    ContageeemM++;
                }
            }
            Dialog_Show(playerid, UparCasa, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}Upgrade Interior", Dialog, "Selecionar", "Fechar");
        }
        case 5:
        {
            if(strcmp(PegarNick(playerid), pCasa[casaid][cDono])) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o tem permiss�o");
            if(pCasa[casaid][cReforma] > gettime()){
                new Mensagem[70];
                format(Mensagem, sizeof(Mensagem), "| ERRO | Voc� s� pode vender sua casa em %s", ConverterSegundos(pCasa[casaid][cReforma]));
                SendClientMessage(playerid, 0xfc520fFF, Mensagem);
                return 1;
            }

            if(!MoveisEntregue(casaid)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� n�o pode vender sua casa ainda pois seus m�veis ainda n�o chegaram");
            if(VerificarSeTemMorador(casaid)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Retire todos os moradores(as) da sua casa");
            if(pCasa[casaid][LixoD] > 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Retire primeiro o lixo de dentro da sua casa");
            if(pCasa[casaid][LixoF] > 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Retire primeiro o lixo de fora da sua casa");
            if(pCasa[casaid][Impostos] > 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Pague os impostos antes de vender!");
            
            strcat(Dialog, "{CCCCCC}1. {FFFFFF}Vender para Servidor\n");
            strcat(Dialog, "{CCCCCC}2. {FFFFFF}Definir Pre�o\n");
            if(pCasa[casaid][cJPreco] > 0) strcat(Dialog, "{CCCCCC}3. {FF0000}Remover Venda");
            Dialog_Show(playerid, VendaEscolha, DIALOG_STYLE_TABLIST, "{00FF00}Venda", Dialog, "Selecionar", "Fechar");   
        }
    }
    return 0;
}

Dialog:ConfirmarVendaCasa(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strcmp(Jogador[playerid][Codigo], inputtext, true)) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | C�digo Inv�lido!");
    new casaid = GetPVarInt(playerid, "InteriorPersonalizadoID"),
        Enviar[300],
        ReformaTotal = (gettime() + (random(48)*3600));

    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Dono`= '*', `LixoF` = 0, `LixoD` = 0, `JPreco` = 0, `Impostos` = 0, `Mensagem` = '*', `Interior` = 1, `Reforma` = %d, `Tranca` = 0, `Morador1` = '*', `Morador2` = '*', `Morador3` = '*', `Morador4` = '*' WHERE `Numero` = %d", ReformaTotal, casaid);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Houve um problema ao vender essa casa!");

    format(Enviar, sizeof(Enviar), "| CASA | O(A) Jogador(a) {00BFFF}%s[%d]{FFFFFF} vendeu sua casa id {00BFFF}%d", pCasa[casaid][cDono], playerid, casaid);
    SendClientMessageToAll(-1, Enviar);

    new InteriorFinal,
        ValorReal,
        vcuzinho;

    if(pCasa[casaid][cInterior] != 1){
        InteriorUpgrade(playerid, casaid, pCasa[casaid][cInterior], InteriorFinal, ValorReal, true);
        vcuzinho += ValorReal;    
    }
    vcuzinho += pCasa[casaid][cPreco];

    new ValorAtual = vcuzinho;
    new Antes = (vcuzinho * 15) / 100; 
    ValorAtual -= Antes;
    
    Jogador[playerid][Dinheiro] += ValorAtual;
    RemoverMoveis(playerid, casaid);

    format(pCasa[casaid][cDono], 90, "*");
    format(pCasa[casaid][cSenha], 90, "*");
    
    if(new i=0; i < MAX_MORADOR; i++)
    {
        if(!strcmp(pMorador[casaid][i][Morador], "*")) continue;
        format(pMorador[casaid][i][Morador], 30, "*");
    }

    pCasa[casaid][cReforma] = ReformaTotal;
    pCasa[casaid][cInterior] = 1;
    pCasa[casaid][cTranca] = 0; 
    pCasa[casaid][cJPreco] = 0;
    pCasa[casaid][LixoF] = 0;
    pCasa[casaid][LixoD] = 0;
    pCasa[casaid][Impostos] = 0;
    AtualizarCasa(casaid);
    cmd_saircasa(playerid);
    return 0;
}

Dialog:ComprarCasaConfimacao(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new i = GetPVarInt(playerid, "CasaIDTartaruga"),
        Enviar[400]
    ;
    if(strcmp(pCasa[i][cDono], "*") && pCasa[i][cJPreco] < 1) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Essa casa j� possui propriet�rio(a)");
    
    if(pCasa[i][cJPreco] > 0){
        if(Jogador[PegarIdPeloNick(pCasa[i][cDono])][Logado] == false) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Voc� precisa esperar o(a) propriet�rio(a) dessa casa ficar online");
    }
    
    new ReformaTotal = (gettime() + (7 * 24 * 60 * 60));
    format(Enviar, sizeof(Enviar), "UPDATE `casas` SET `Dono`='%s', `Reforma`=%d, `Morador0` = '*', `Morador1` = '*', `Morador2` = '*', `Morador3` = '*', `Morador4` = '*', `Morador5` = '*', `JPreco` = 0, `Mensagem` = '*', `Senha` = '*', `Tranca` = 0 WHERE `Numero`=%d", EscapeString(PegarNick(playerid)), ReformaTotal, i);
    mysql_query(IDConexao, Enviar, false);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Houve um problema ao comprar essa casa");
    
    new Mensagem[128];
    if(pCasa[i][cJPreco] > 0)
    {
        format(Mensagem, sizeof(Mensagem), "| CASA | O(A) Jogador(a) {00BFFF}%s[%d]{FFFFFF} comprou a casa {FFFF00}%d{FFFFFF} do(a) jogador(a) {00BFFF}%s", PegarNick(playerid), playerid, i, pCasa[i][cDono]);
        Jogador[playerid][Dinheiro] -= pCasa[i][cJPreco];
        Jogador[PegarIdPeloNick(pCasa[i][cDono])][Dinheiro] += pCasa[i][cJPreco];
        SendClientMessageToAll(0xDCDCDCFF, Mensagem);
    
        format(Mensagem, sizeof(Mensagem), "| VENDA | Sua casa foi comprada pelo(a) jogador(a) {FF0000}%s[%d]{FFFFFF} por {00FF00}$%s", PegarNick(playerid), playerid, DinheiroSeparar(pCasa[i][cJPreco]));
        SendClientMessage(PegarIdPeloNick(pCasa[i][cDono]), -1, Mensagem);

        format(Mensagem, sizeof(Mensagem), "| COMPRA | Voc� comprou essa casa por {00FF00}$%s", DinheiroSeparar(pCasa[i][cJPreco]));
        SendClientMessage(playerid, -1, Mensagem);

        // RemoverMoveis(PegarIdPeloNick(pCasa[i][cDono]), i); // Vender os m�veis dele

        format(Enviar, sizeof(Enviar), "UPDATE `moveis` SET `Nome` = '%s' WHERE `Nome` = '%s'", EscapeString(PegarNick(playerid)), EscapeString(pCasa[i][cDono]));
        mysql_query(IDConexao, Enviar, false);
        if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Houve um problema ao alterar os m�veis");

    }
    else
    {
        format(Mensagem, sizeof(Mensagem), "| CASA | O(A) Jogador(a) %s[%d] comprou a casa %d localizada em %s", PegarNick(playerid), playerid, i, GetPlayerZone(playerid));
        Jogador[playerid][Coins] -= pCasa[i][cCoins];
        Jogador[playerid][Dinheiro] -= pCasa[i][cPreco]; 
        SendClientMessageToAll(0xDCDCDCFF, Mensagem);
    }

    if(new d=0; d < MAX_MORADOR; d++)
    {
        if(!strcmp(pMorador[i][d][Morador], "*")) continue;
        format(pMorador[i][d][Morador], 30, "*");
    }

    // Setando Informa��es e resetando outras
    pCasa[i][cJPreco] = 0;
    pCasa[i][cTranca] = 0;
    pCasa[i][Impostos] = 0;
    pCasa[i][cReforma] = ReformaTotal;
    format(pCasa[i][cDono], 90, PegarNick(playerid));
    format(pCasa[i][cSenha], 90, "*");
    format(pCasa[i][cMensagem], 90, "*");
    
    AtualizarCasa(i);
    EntrarCasa(playerid, i);
    return 0;
}