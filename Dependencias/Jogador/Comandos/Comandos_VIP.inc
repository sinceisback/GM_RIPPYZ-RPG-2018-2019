CMD:comandosvip(playerid)
{
    if(Jogador[playerid][Admin] < 1 && Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    new DialogVIP[700];
    strcat(DialogVIP, "{43e69c}/Vencimento{FFFFFF} - Para visualizar o vencimento do seu VIP\n");
    strcat(DialogVIP, "{43e69c}/Jetpack{FFFFFF} - Para pegar uma mochila ajato ( JetPack )\n");
    strcat(DialogVIP, "{43e69c}/Pintar [Cor1] [Cor2]{FFFFFF} - Para pintar o ve�culo que voc� esteja dirigindo\n"); 
    strcat(DialogVIP, "{43e69c}/Colete{FFFFFF} - Para pegar um colete VIP\n");
    strcat(DialogVIP, "{43e69c}/Reparar{FFFFFF} - Para reparar seu ve�culo atual\n");
    strcat(DialogVIP, "{43e69c}/Virar{FFFFFF} - Para destombar seu ve�culo\n");
    //strcat(DialogVIP, "{43e69c}/Clima{FFFFFF} - Para ativar/desativar climas personalizados\n");
    strcat(DialogVIP, "{43e69c}/Neon{FFFFFF} - Para adicionar neon em seu ve�culo\n");
    strcat(DialogVIP, "{43e69c}/v [Mensagem]{FFFFFF} - Para enviar mensagem no chat VIP\n");
    //strcat(DialogVIP, "{43e69c}/sVip{FFFFFF} - Para desativar ou ativar o chat VIP\n");
    strcat(DialogVIP, "{43e69c}/CorVIP{FFFFFF} - Para alterar a cor da sua tag");
    Dialog_Show(playerid, ComandosVIPInformacao, DIALOG_STYLE_MSGBOX, "{FF0000}Comandos VIP", DialogVIP, "Fechar", #);
    return 1;
}

CMD:comandosnitro(playerid)
{
    if(Jogador[playerid][Admin] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    new DialogNitro[600];
    strcat(DialogNitro, "{43e69c}/Jetpack{FFFFFF} - Para pegar uma mochila ajato ( JetPack )\n");
    strcat(DialogNitro, "{43e69c}/Virar{FFFFFF} - Para destombar seu ve�culo");
    Dialog_Show(playerid, ComandosNitroInformacao, DIALOG_STYLE_MSGBOX, "{FF0000}Comandos Nitro", DialogNitro, "Fechar", #);
    return 1;
}

CMD:vencimento(playerid)
{
    if(Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    new Vencimento[90];
    format(Vencimento, sizeof(Vencimento), "{00BFFF}Vencimento do VIP:{FFFFFF} %s", ConverterSegundos(Jogador[playerid][Vip]));
    Dialog_Show(playerid, VencimentoVIP, DIALOG_STYLE_MSGBOX, "{FFFFFF}Vencimento", Vencimento, "Fechar", #);
    return 1;
}

CMD:jetpack(playerid)
{
    if(Jogador[playerid][Admin] < 1 && Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    if(Jogador[playerid][Estrelas] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� procurado(a)");
    if(pModo[playerid][Jogando] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� em um modo de jogo!");
    if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� em um ve�culo!");
    if(GetPlayerSpeed(playerid) > 6) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� deve estar parado(a)");
    if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� est� em uma jetpack");
    if(GetPlayerInterior(playerid) > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar jetpack no interior");
    if(cAC[playerid][Travado] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar jetpack agora");

    SendClientMessage(playerid, 0x00FF00FF, "| VIP | Voc� pegou uma jetpack");
    SetPVarInt(playerid, "AntiJetPack", 1);
    SetPVarInt(playerid, "AntiJetPackAviso", 0);
    SetPlayerSpecialAction(playerid, 2);
    return 1;
}

CMD:virar(playerid)
{
    if(Jogador[playerid][Admin] < 1 && Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� em um ve�culo!");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� dirigindo!");
    if(GetPVarInt(playerid, "ProibidoReparo") == 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode virar!");
    new Veiculo;
    new Float:Angulo;
    Veiculo = GetPlayerVehicleID(playerid);
    GetVehicleZAngle(Veiculo, Angulo);
    SetVehicleZAngle(Veiculo, Angulo);
    return 1;
}

CMD:pintar(playerid, params[])
{
    if(Jogador[playerid][Admin] < 2 && Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� em um ve�culo!");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� dirigindo!");
    new cor1,
        cor2;
    if(sscanf(params, "dd", cor1, cor2)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /pintar [Cor1] [Cor2]");
    ChangeVehicleColor(GetPlayerVehicleID(playerid), cor1, cor2);
    SendClientMessage(playerid, 0x00FF00FF, "| VIP | Ve�culo pintado com sucesso!");
    return 1;
}

CMD:reparar(playerid, params[])
{
    if(Jogador[playerid][Admin] < 1 && Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� em um ve�culo!");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� dirigindo!");
    if(pAbordado[playerid][Acompanhando] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode utilizar esse comando agora");
    if(GetPVarInt(playerid, "AntiAbordagem") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� iniciou ou acabou de finalizar uma a��o, aguarde!");
    if(GetPVarInt(playerid, "ProibidoReparo") == 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode reparar!");
    SendClientMessage(playerid, 0x00FF00FF, "| VIP | Ve�culo reparado com sucesso!");
    RepairVehicle(GetPlayerVehicleID(playerid));
    return 1;
}

CMD:v(playerid, params[])
{
    if(Jogador[playerid][Vip] < gettime() && Jogador[playerid][Admin] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    if(Jogador[playerid][BlockChatVip] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� bloqueou o chat vip");
    if(Jogador[playerid][Mutado] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� foi mutado(a) pela administra��o, aguarde.");
    new Mensagem[128];
    if(sscanf(params, "s[128]", Mensagem)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /V [Mensagem]");
    if(strlen(Mensagem) > 84) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Mensagem muito grande!");
    new Formatacao[128],
        zTagg[20]; 

	if(Jogador[playerid][BaseID] > 0) strcatEx(zTagg, "[%s]", Base[Jogador[playerid][BaseID]][BaseTag]);
    format(Formatacao, sizeof(Formatacao), "| CHAT-VIP | %s%s[%d]: %s", zTagg, PegarNick(playerid), playerid, Mensagem);

    for(new i=0; i < MAX_PLAYERS; i++){
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(Jogador[i][BlockChatVip] == true) continue;
        if(GetPVarInt(i, "EventoJogador") > 0) continue;
        if(Jogador[i][Admin] > 0 || Jogador[i][Vip] > gettime()){
            SendClientMessage(i, 0x00BFFFFF, Formatacao);
        }
    }

    return 1;
}

/*CMD:svip(playerid, params[])
{
    if(Jogador[playerid][Admin] < 1 && Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    if( == false){
        SendClientMessage(playerid, 0x00FF00FF, "| CHAT-VIP | Voc� desativou o Chat-VIP");
        Jogador[playerid][BlockChatVip] = true;
    }else{
        SendClientMessage(playerid, 0x00FF00FF, "| CHAT-VIP | Voc� ativou o Chat-VIP");
        Jogador[playerid][BlockChatVip] = false;  
    }
    return 1;
}*/

CMD:vips(playerid)
{
    new DialogVIP[2000];
    strcat(DialogVIP, "Membros\n");
    for(new i=0; i < MAX_PLAYERS; i++){
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Admin] < 1 && Jogador[i][Vip] > gettime()){
            strcatEx(DialogVIP, "{00BFFF}%s[%d]\n", PegarNick(i), i);
        }
    }
    Dialog_Show(playerid, VipsOnlineDialog, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}Vips", DialogVIP, "Fechar", #);
    return 1;
}

CMD:corvip(playerid)
{
    if(Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    Dialog_Show(playerid, VipCorAlterar, DIALOG_STYLE_INPUT, "{FF0000}Cor VIP", "{FFFFFF}Coloque abaixo uma cor hexadecimal para sua tag", "Definir", "Cancelar");   
    return 1;
}

CMD:colete(playerid)
{
    if(Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    if(GetPVarInt(playerid, "ColeteTempo") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco.");
    SetPVarInt(playerid, "ColeteTempo", gettime()+900);
    SetPlayerArmour(playerid, 100.0);
    SendClientMessage(playerid, 0x228B22FF, "| COLETE | Voc� pegou um colete");
    return 1;
}