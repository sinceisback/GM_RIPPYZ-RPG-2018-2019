function CortandoArvore(processo, copia, playerid)
{
    new id = Lenhador[playerid][SuaLenhaID];

    // Progresso
    if(processo == 1)
    {
        Lenhador[playerid][StatusLenha] = 2;
        Lenha[id][LenhaQuebrada] = true;

        // Setando informa��es
        TogglePlayerControllable(playerid, 1);
        ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0);

        DestroyDynamicObjectEx(Lenha[id][LenhaObjeto]);
        Lenha[id][LenhaObjeto] = CreateDynamicObject(832, LenhaLoad[id][LenhaLPosX], LenhaLoad[id][LenhaLPosY], LenhaLoad[id][LenhaLPosZ], LenhaLoad[id][LenhaLRotX], LenhaLoad[id][LenhaLRotY], LenhaLoad[id][LenhaLRotZ], 0, 0, -1, 500.0, 500.0, -1);   

        // Criar Texto
        UpdateDynamic3DTextLabelText(LenhaTexto[copia], 0xFFFFFFFF, "{32CD32}Madeireira{FFFFFF}\nAperte {CCCCCC}N{FFFFFF} para pegar as madeiras");

        // Temporizador
        Lenhador[playerid][LenhaTempo] = SetTimerEx("CortandoArvore", 20000, false, "ddd", 2, id, playerid);
        SendClientMessage(playerid, 0xFFFF00FF, "| MADEIREIRA | Sua �rvore foi derrubada e cortada, v� at� ela e pegue as madeiras");
    }


    // Verifica��o
    else if(processo == 2)
    {
        Lenhador[playerid][StatusLenha] = 0;
        Lenhador[playerid][LenhaQuebrando] = false;
        Lenhador[playerid][LenhaTempo] = SetTimerEx("CortandoArvore", 20000, false, "ddd", 3, id, playerid);   
        UpdateDynamic3DTextLabelText(LenhaTexto[copia], 0xFFFFFFFF, "{32CD32}Madeireira{FFFFFF}\nEssa �rvore n�o foi colhida no tempo!");
        SendClientMessage(playerid, 0xFFFF00FF, "| MADEIREIRA | Voc� demorou muito para pegar as madeiras, portanto o servi�o foi cancelado");
    }

    // Regenera��o
    else if(processo == 3)
    {
        Lenha[copia][LenhaSendoUsada] = false; 
        Lenha[copia][LenhaQuebrada] = false;
        DestroyDynamicObjectEx(Lenha[copia][LenhaObjeto]);
        Lenha[copia][LenhaObjeto] = CreateDynamicObject(654, LenhaLoad[copia][LenhaLPosX], LenhaLoad[copia][LenhaLPosY], LenhaLoad[copia][LenhaLPosZ], LenhaLoad[copia][LenhaLRotX], LenhaLoad[copia][LenhaLRotY], LenhaLoad[copia][LenhaLRotZ], 0, 0, -1, 500.0, 500.0, -1); 
        UpdateDynamic3DTextLabelText(LenhaTexto[copia], 0xFFFFFFFF, "{32CD32}Madeireira{FFFFFF}\nDispon�vel");
    }
    return 1;
}


