#include <YSI_Coding\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
    if(pLocalizacao[playerid][Localizando] == true){
        KillTimer(pLocalizacao[playerid][TemporizadorLoc]);
        DestroyDynamicMapIconEx(pLocalizacao[playerid][MapIconLoc]);
    }

    if(pLocalizacao[playerid][vLocalizando] == true) DestroyDynamicRaceCPEx(pLocalizacao[playerid][vCheckLoc]);    

    // Limpando informa��es
    new Popo[LocalizacaoInfo];
    pLocalizacao[playerid] = Popo;
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, checkpointid)
{
    if(checkpointid == pLocalizacao[playerid][vCheckLoc] && pLocalizacao[playerid][vLocalizando] == true){
        pLocalizacao[playerid][vLocalizando] = false;
        DestroyDynamicRaceCPEx(pLocalizacao[playerid][vCheckLoc]);  
    }
    return 1;
}

function LocalizarProcurado(playerid, procurado)
{
    new Float:pCpos[3];
    GetPlayerPos(procurado, pCpos[0], pCpos[1], pCpos[2]);
    if(!IsPlayerConnected(procurado))
    {
        new Mensagem[128];
        format(Mensagem, sizeof(Mensagem), "| INFO | O(A) Jogador(a) localizado(a) %s desconectou-se do servidor", PegarNick(procurado));
        SendClientMessage(playerid, 0x32CD32FF, Mensagem);
        PararLocalizador(playerid);
        return 1;
    }
    else if(Jogador[procurado][Preso] > 0)
    {
        new Mensagem[128];
        format(Mensagem, sizeof(Mensagem), "| INFO | O(A) Jogador(a) %s foi preso(a)", PegarNick(procurado));
        SendClientMessage(playerid, 0x32CD32FF, Mensagem);
        PararLocalizador(playerid);
        return 1;    
    }
    else if(IsPolicia(playerid) && Jogador[procurado][Estrelas] < 1 && strcmp(Jogador[playerid][Profissao], "Corregedoria"))
    {
        new Mensagem[128];
        format(Mensagem, sizeof(Mensagem), "| INFO | O(A) Jogador(a) %s n�o est� mais procurado(a)", PegarNick(procurado));
        SendClientMessage(playerid, 0x32CD32FF, Mensagem);
        PararLocalizador(playerid);
        return 1;
    }
    else if(IsPlayerInRangeOfPoint(playerid, 8.0, pCpos[0], pCpos[1], pCpos[2]))
    {
        new Mensagem[128];
        format(Mensagem, sizeof(Mensagem), "| INFO | Voc� chegou no(a) jogador(a) localizado(a) %s[%d]", PegarNick(procurado), procurado);
        SendClientMessage(playerid, 0x32CD32FF, Mensagem);
        PararLocalizador(playerid);
        return 1;
    }
    
    new Mensagem[198];
    //idx = GetPVarInt(procurado, "InteriorPersonalizadoID");
    
    format(Mensagem, sizeof(Mensagem), "Localizando~n~~b~%s[%d]~w~ | ~r~%0.2fKm~w~", PegarNick(procurado), procurado, GetPlayerDistanceFromPoint(playerid, pCpos[0], pCpos[1], pCpos[2]));
    
    /*if(Jogador[procurado][uInteriorEx] == 1 || 
    Jogador[procurado][uInteriorEx] == 2 || 
    Jogador[procurado][uInteriorEx] == 6)
    {
        switch(Jogador[procurado][uInteriorEx])
        {
            case 1:
            {
                strcatEx(Mensagem, "~y~%s~w~~n~Casa: ~g~%d", AreaNome(pCasa[idx][cPosicaoX], pCasa[idx][cPosicaoY], pCasa[idx][cPosicaoZ]), idx);
                pCpos[0] = pCasa[idx][cPosicaoX];
                pCpos[1] = pCasa[idx][cPosicaoY];
                pCpos[2] = pCasa[idx][cPosicaoZ];
            }
            case 2.6:
            {
                strcatEx(Mensagem, "~y~%s~w~~n~Empresa: ~g~%d", AreaNome(pEmpresa[idx][ePosicaoX], pEmpresa[idx][ePosicaoY], pEmpresa[idx][ePosicaoZ]), idx);
                pCpos[0] = pEmpresa[idx][ePosicaoX];
                pCpos[1] = pEmpresa[idx][ePosicaoY];
                pCpos[2] = pEmpresa[idx][ePosicaoZ];
            }
        }
    }
    else if(Jogador[procurado][uInterior] > 0)
    {
        idx = Jogador[procurado][uInterior];
        strcatEx(Mensagem, "~y~%s~w~~n~Local: ~g~%s", AreaNome(Pick[idx][EntradaX], Pick[idx][EntradaY], Pick[idx][EntradaZ]), Pick[idx][MensagemPickup]);
        pCpos[0] = Pick[idx][EntradaX];
        pCpos[1] = Pick[idx][EntradaY];
        pCpos[2] = Pick[idx][EntradaZ];
    }
    else strcatEx(Mensagem, "~y~%s", AreaNome(pCpos[0], pCpos[1], pCpos[2]));*/
    PlayerTextDrawSetString(playerid, LocalizarComando[playerid][0], ConverterTexto(Mensagem));
    DestroyDynamicMapIconEx(pLocalizacao[playerid][MapIconLoc]);
    pLocalizacao[playerid][MapIconLoc] = CreateDynamicMapIcon(pCpos[0], pCpos[1], pCpos[2], 0, 0xFF0000FF, -1, -1, playerid, 99999.9, MAPICON_GLOBAL);
    return 1;
}

stock PararLocalizador(playerid)
{
    KillTimer(pLocalizacao[playerid][TemporizadorLoc]);
    DestroyDynamicMapIconEx(pLocalizacao[playerid][MapIconLoc]);
    pLocalizacao[playerid][Localizando] = false;
    OcultarLocalizador(playerid);
    return 1;
}

CMD:localizar(playerid, params[])
{
    if(!IsPolicia(playerid) && strcmp(Jogador[playerid][Profissao], "Mecanico") && Jogador[playerid][Admin] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    
    new id;
    if(sscanf(params, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Localizar [ID]");
    if(id == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode se localizar");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador n�o encontrado(a)");

    if(IsPolicia(playerid))
    {
        if(Jogador[id][Admin] > 0 && pAdmin[id][FalsoPlayer] == false && Jogador[playerid][Admin] != 7) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode localizar um administrador");
        if(pLocalizacao[playerid][PontoTempo] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse comando est� bloqueado, aguarde um pouco.");
        if(!strcmp(Jogador[playerid][Profissao], "Corregedoria"))
        {
            if(!IsPolicia(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse jogador n�o � um(a) policial");
        }
        else
        {
            if(pPolicia[playerid][PegouUniformePolicia] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� sem uniforme policial");
            if(!VerificarPolicia(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� sem ve�culo policial");
            //if(pLocalizacao[playerid][UltimoPolicia] != pLocalizacao[playerid][PoliciaCarroID]) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Seu �ltimo ve�culo n�o � o seu da policia");
            if(Jogador[id][Estrelas] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse jogador n�o esta procurado(a)");
            if(Jogador[id][Preso] != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse jogador est� preso(a)");
        }

        if(Jogador[playerid][Admin] < 1)
        {
            new MensagemEx[128];
            format(MensagemEx, sizeof(MensagemEx), "| POL�CIA | O(A) Policial %s[%d] est� localizando %s[%d]", PegarNick(playerid), playerid, PegarNick(id), id);
            for(new i=0; i < MAX_PLAYERS; i++)
            {
                if(!IsPlayerConnected(i)) continue;
                if(Jogador[i][Logado] == false) continue;
                if(strcmp(Jogador[i][Profissao], "Corregedoria")) continue;
                SendClientMessage(i, 0x1E90FFFF, MensagemEx);
            }
        }
    }
    
    if(pLocalizacao[playerid][Localizando] == true) PararLocalizador(playerid);

    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "| LOCALIZADOR | Voc� est� localizando o(a) %s[%d]", PegarNick(id), id);
    SendClientMessage(playerid, 0x00BFFFFF, Mensagem);

    MostrarLocalizador(playerid);
    pLocalizacao[playerid][Localizando] = true;
    pLocalizacao[playerid][TemporizadorLoc] = SetTimerEx("LocalizarProcurado", 3000, true, "dd", playerid, id);
    pLocalizacao[playerid][PontoTempo] = gettime()+60; //Delay do Comando
    return 1;
}

CMD:deslocalizar(playerid)
{
    //if(!IsPolicia(playerid) || ) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    if(pLocalizacao[playerid][Localizando] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� localizando ningu�m");
    PararLocalizador(playerid);
    SendClientMessage(playerid, 0x00BFFFFF, "| LOCALIZADOR | Voc� n�o est� mais localizando");
    return 1;
}

stock MarcarPosicao(playerid, Float:X, Float:Y, Float:Z)
{
    if(pLocalizacao[playerid][vLocalizando] == true){
        DestroyDynamicRaceCPEx(pLocalizacao[playerid][vCheckLoc]); 
        pLocalizacao[playerid][vCheckLoc] = INVALID_STREAMER_ID;
    }
    pLocalizacao[playerid][vLocalizando] = true;
    pLocalizacao[playerid][vCheckLoc] = CreateDynamicRaceCP(2, X, Y, Z, 0.0, 0.0, 0.0, 2.0, 0, 0, playerid, 999999.9);
    return 1;
}

stock VerificarMarcacao(playerid)
{
    if(pLocalizacao[playerid][vLocalizando] == true){
        DestroyDynamicRaceCPEx(pLocalizacao[playerid][vCheckLoc]);
        pLocalizacao[playerid][vCheckLoc] = INVALID_STREAMER_ID;
        pLocalizacao[playerid][vLocalizando] = false;
    } 
    return 1;
}