#include <YSI_Coding\y_hooks>

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_PASSENGER)
    {
        if(pUber[playerid][StatusChamado] == 0) return 1;

        new id = pUber[playerid][UberID];
        if(GetPlayerVehicleID(playerid) != pUber[id][UberVeiculo]) return 1;

        new Mensagem[128];

        MostrarUber(playerid);
        MostrarUber(id);

        format(Mensagem, sizeof(Mensagem), "Passegeiro(a)_~y~%s", PegarNick(playerid));
        PlayerTextDrawSetString(id, UberTxd[id][3], Mensagem);
        format(Mensagem, sizeof(Mensagem), "Motorista(a)_~y~%s", PegarNick(id));
        PlayerTextDrawSetString(playerid, UberTxd[playerid][3], Mensagem);

        pUber[playerid][StatusChamado] = 2; // Atendido(a)
        pUber[id][UberValor] = 0;
        pUber[id][UberTemporizador] = SetTimerEx("AtualizarUber", 2000, true, "d", id);
    }

    else if(oldstate == PLAYER_STATE_PASSENGER)
    {
        if(pUber[playerid][StatusChamado] == 0) return 1;
        if(pUber[playerid][StatusChamado] != 2) return 1;

        new id = pUber[playerid][UberID],
            Mensagem[128]
        ;

        KillTimer(pUber[id][UberTemporizador]);

        OcultarUber(playerid);
        OcultarUber(id);

        Jogador[id][Dinheiro] += pUber[id][UberValor];
        Jogador[playerid][Dinheiro] -= pUber[id][UberValor];
        format(Mensagem, sizeof(Mensagem), "| UBER | Voc� recebeu $%s pela corrida", DinheiroSeparar(pUber[id][UberValor]));
        SendClientMessage(id, 0xFFFF00FF, Mensagem);
               
        format(Mensagem, sizeof(Mensagem), "| UBER | Voc� pagou $%s pela corrida", DinheiroSeparar(pUber[id][UberValor]));
        SendClientMessage(playerid, 0xFFFF00FF, Mensagem);

        //UberID
        pUber[id][UberAtendeu] = false;

        //Passageiro
        pUber[playerid][StatusChamado] = 0;
    }
    return 1;
}

CMD:cancelar(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Uber")) return 0;
    if(pUber[playerid][UberAtendeu] == true)
    {
        new id = pUber[playerid][PassageiroID],
            Mensagem[128]
        ;

        pUber[id][StatusChamado] = 0;
        pUber[playerid][UberAtendeu] = false;
        KillTimer(pUber[playerid][UberTemporizador]);
        DestroyDynamicMapIconEx(pUber[playerid][UberIcone]);
        DestroyDynamicMapIconEx(pUber[id][UberIcone]);

        format(Mensagem, sizeof(Mensagem), "| UBER | %s[%d] cancelou seu chamado", PegarNick(playerid), playerid);
        SendClientMessage(id, 0xFFFF00FF, Mensagem);
        SendClientMessage(playerid, 0xFFFF00FF, "| UBER | Chamado cancelado com sucesso!");
        return 1;
    }
    SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� atendeu ou n�o tem nenhuma solicita��o aceita");
    return 1;
}