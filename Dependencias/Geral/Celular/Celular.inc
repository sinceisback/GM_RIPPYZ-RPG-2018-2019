#include <YSI_Coding\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
    if(pCelularEx[playerid][CellAberto] == true) KillTimer(pCelularEx[playerid][CellTID]);

    rRecente[playerid] = 0;
    for(new i=0; i < 3; i++){
        new Delet331231ar[UltimasLigacoes];
        rCelular[playerid][i] = Delet331231ar;    
    }

    new Delet31231ar[CelularPInfo];
    pCelularEx[playerid] = Delet31231ar; 
    
    return 1;
}

Dialog:ChamarMecanicoMensagem(playerid, response, listitem, inputtext[]) 
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) > 20) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Texto muito grande");
    if(Jogador[playerid][Operadora] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o possui um CHIP");
    if(ChamadoMec[playerid][ChamouMecanico] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco antes de chamar novamente um reboque");
    if(ChamadoMec[playerid][FuiAtendido] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� solicitou um(a) mec�nico(a)");

    new Float:mas[3],
        bool:asdas;
    
    GetPlayerPos(playerid, mas[0], mas[1], mas[2]);
    for(new i=0; i < MAX_VEHICLES; i++)
    {
        if(VeiculoServer[i][VeiculoOn] == false) continue;
        if(!IsVehicleInRangeOfPoint(i, 3.0, mas[0], mas[1], mas[2])) continue;
        if(VeiculoServer[i][vQuebrado] == false) return SendClientMessage(playerid, 0xfc520fFF, "| ERRO | Esse ve�culo n�o est� quebrado");
        ChamadoMec[playerid][VeiculoReparo] = i;
        asdas = true;
        break;
    }
    if(asdas == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� perto de nenhum ve�culo quebrado");

    new Mensagem[238],
        Mecanc = 0,
        Ersodsa;
    
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(i == playerid) continue;
        if(Jogador[i][Logado] == false) continue;
        if(strcmp(Jogador[i][Profissao], "Mec�nico")) continue;
        if(pMecanico[i][MecanicoAlugado] == false) continue;
        if(pMecanico[i][AtendendoMec] == true) continue;
        format(Mensagem, sizeof(Mensagem), "| MEC�NICO | O(A) Jogador(a) {00BFFF}%s[%d]{FFFFFF} est� solicitando mec�nico em %s, mande sua proposta.", PegarNick(playerid), playerid, GetPlayerZone(playerid));
        SendClientMessage(i, -1, Mensagem);
        Mecanc++;
    }
    if(Mecanc == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | N�o h� mecanicos(as) dispon�veis no momento!");
    else if(Mecanc == 0 && Ersodsa > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem dinheiro sucifiente para pegar um mec�nico mais pr�ximo");
    else SendClientMessage(playerid, -1, "| CELULAR | Seu chamado foi enviado com sucesso, aguarde uma resposta.");
    ChamadoMec[playerid][ChamouMecanico] = gettime()+60;
    return 1;
}

Dialog:MensagemParamedicos(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) > 30) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Texto muito grande");
    if(GetPVarInt(playerid, "TempoDenuA") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco!");
    SetPVarInt(playerid, "TempoDenuA", gettime()+40);
    new Mensagem[148];
    format(Mensagem, sizeof(Mensagem), "| CENTRAL | %s[%d] enviou uma solicita��o: %s", PegarNick(playerid), playerid, inputtext);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(strcmp(Jogador[i][Profissao], "Param�dico") && Jogador[i][Admin] < 2) continue;
        if(Jogador[i][Admin] < 2){
            if(pPolicia[i][PegouUniformePolicia] == false) continue;
        }
        SendClientMessage(i, 0x4682B4FF, Mensagem);
    }
    SendClientMessage(playerid, 0x4682B4FF, "| CENTRAL | Sua solita��o foi enviada para os param�dicos");
    return 1;
}

Dialog:MensagemPolicia(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    if(strlen(inputtext) > 30) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Texto muito grande");
    if(Jogador[playerid][Estrelas] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� procurado(a)");
    if(GetPVarInt(playerid, "TempoDenu") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco!");
    SetPVarInt(playerid, "TempoDenu", gettime()+60);
    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "| CENTRAL | %s[%d] fez uma den�ncia: %s", PegarNick(playerid), playerid, inputtext);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(!IsPolicia(i) && Jogador[i][Admin] < 2) continue;
        if(Jogador[i][Admin] < 2){
            if(pPolicia[i][PegouUniformePolicia] == false) continue;
        }
        SendClientMessage(i, 0x4682B4FF, Mensagem);
    }
    SendClientMessage(playerid, 0x4682B4FF, "| CENTRAL | Seu chamado foi enviado para os policias");
    return 1;
}


hook OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
    // Voltar ou Fechar
    if(playertextid == CelularCapa[playerid][6])
    {
        if(GetPVarInt(playerid, "EmLigacao") > 0){
            new id = GetPVarInt(playerid, "LigacaoID");
            RecusarChamada(playerid);
            RecusarChamada(id);
        }

        if(!strcmp(pCelularEx[playerid][PagOcultarCelular], "OcultarCelular")) OcultarHome(playerid);
        CallRemoteFunction(pCelularEx[playerid][PagOcultarCelular], "d", playerid);
        if(strcmp(pCelularEx[playerid][PagMostrarCelular], "*")) CallRemoteFunction(pCelularEx[playerid][PagMostrarCelular], "d", playerid); 
    }

    // Banco - Tansfer�ncia - Saldo etc..
    else if(playertextid == CelularHome[playerid][14]){
        OcultarHome(playerid);
        MostrarCelularBanco(playerid);
        return Y_HOOKS_BREAK_RETURN_1;
    }

    // Policia
    else if(playertextid == CelularHome[playerid][4]){
        Dialog_Show(playerid, MensagemPolicia, DIALOG_STYLE_INPUT, "{FF0000}190", "Coloque o problema que est� acontecendo abaixo", "Confirmar", "Cancelar");
        return Y_HOOKS_BREAK_RETURN_1;  
    }

    // Param�dicos
    else if(playertextid == CelularHome[playerid][6]){
        Dialog_Show(playerid, MensagemParamedicos, DIALOG_STYLE_INPUT, "{FF0000}192", "Coloque o problema que est� acontecendo abaixo", "Confirmar", "Cancelar");
        return Y_HOOKS_BREAK_RETURN_1;  
    }
    
    // Agenda
    else if(playertextid == CelularHome[playerid][0]){ 
        OcultarHome(playerid);
        MostrarAgendaOP(playerid);
        return Y_HOOKS_BREAK_RETURN_1;
    }

    // MP3
    else if(playertextid == CelularHome[playerid][12])
    {
        if(Jogador[playerid][MP4] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o comprou o MP3, v� at� uma loja de utilit�rios.");
        MostrarRadio(playerid);
        return Y_HOOKS_BREAK_RETURN_1;
    }

    // GPS
    else if(playertextid == CelularHome[playerid][10])
    {
        if(Jogador[playerid][Gps] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o comprou o GPS, v� at� uma loja de utilit�rios.");
        MostrarGPS(playerid);
        return Y_HOOKS_BREAK_RETURN_1;
    }

    // Chamar Uber
    else if(playertextid == CelularHome[playerid][8]){
        OcultarHome(playerid);
        MostrarCelularUber(playerid);
        return Y_HOOKS_BREAK_RETURN_1; 
    }

    // Chamer Mec�nico
    else if(playertextid == CelularHome[playerid][2]){
        Dialog_Show(playerid, ChamarMecanicoMensagem, DIALOG_STYLE_INPUT, "{FF0000}Mec�nico", "Coloque o problema que est� acontecendo abaixo", "Confirmar", "Cancelar");
        return Y_HOOKS_BREAK_RETURN_1;    
    }

    else if(playertextid == CelularHome[playerid][16]){
        OcultarHome(playerid);
        MostrarOlx(playerid); 
        return Y_HOOKS_BREAK_RETURN_1;    
    }

    return 0;
}

CMD:celular(playerid)
{
    if(Jogador[playerid][Celular] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o possui um celular");
    if(GetPVarInt(playerid, "CerulaAberto") == 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� est� segurando o celular");
    SetPVarInt(playerid, "CerulaAberto", 1);
    RequestCelular(playerid);
    return 1;
}