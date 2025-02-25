#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    CreateDynamic3DTextLabel("{00BFFF}Mec�nica\n{FFFFFF}Aperte {CCCCCC}'Y'{FFFFFF} para alugar/devolver", -1, 313.2029,-18.0681,1.5781, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0,  0, -1);
    CreateDynamicPickup(1239, 1, 313.2029,-18.0681,1.5781, 0, 0, -1, 50.0);
    //
    CreateDynamic3DTextLabel("{00BFFF}Mec�nica - Loja\n{FFFFFF}Aperte {CCCCCC}'Y'", -1, 326.5619,-53.5201,1.5268, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0,  0, -1);
    CreateDynamicPickup(1239, 1, 326.5619,-53.5201,1.5268, 0, 0, -1, 50.0);
    return 1;
}

CMD:mecanicoaceitar(playerid, params[])
{
    if(strcmp(Jogador[playerid][Profissao], "Mec�nico")) return 0;
    if(pMecanico[playerid][AtendendoMec] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� atendeu um(a) jogador(a)");

    new id, vllr;
    if(sscanf(params, "dd", id, vllr)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /MecanicoAceitar [ID] [Pre�o]");
    if(id == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode se atender");
    if(vllr < 1500) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Valor m�nimo R$1.500");
    if(vllr > 7000) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Valor m�ximo R$7.000");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) n�o est� conectado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) n�o est� logado(a)");
    if(ChamadoMec[id][ChamouMecanico] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) n�o solicitou nenhum mec�nico");
    if(ChamadoMec[id][FuiAtendido] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) j� foi atendido(a)");
    if(MecQuery[id][playerid] != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� enviou proposta para esse(a) jogador(a), aguarde.");

    MecQuery[id][playerid] = vllr;

    new Mensagem[158];
    format(Mensagem, sizeof(Mensagem), "| MEC�NICO | O(A) Mec�nico(a) {FFA500}%s[%d]{FFFFFF} enviou uma solicita��o por {32CD32}$%s{FFFFFF} ( /MecanicoConfirmar )", PegarNick(playerid), playerid, DinheiroSeparar(vllr));
    SendClientMessage(id, -1, Mensagem);

    format(Mensagem, sizeof(Mensagem), "| MEC�NICO | Voc� enviou uma solicita��o para {FFA500}%s[%d]{FFFFFF} por {32CD32}$%s", PegarNick(id), id, DinheiroSeparar(vllr));
    SendClientMessage(playerid, -1, Mensagem);
    return 1;
}

CMD:mecanicoconfirmar(playerid, params[])
{
    if(ChamadoMec[playerid][ChamouMecanico] < gettime()) return 0;
    new id;
    if(sscanf(params, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /MecanicoConfirmar [ID]");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) n�o est� conectado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) n�o est� logado(a)");
    if(MecQuery[playerid][id] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) n�o enviou nada para voc�");
    if(pMecanico[id][AtendendoMec] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | O(A) Jogador(a) j� est� atendendo.");

    ChamadoMec[playerid][ChamouMecanico] = 0;
    SetPVarInt(id, "ASDASDASDSADA", MecQuery[playerid][id]);

    for(new i=0; i < MAX_PLAYERS; i++){
        MecQuery[playerid][i] = 0;
    }

    new idx = ChamadoMec[playerid][VeiculoReparo],
        Float:Jisa[3],
        Mensagem[128];

    ChamadoMec[playerid][FuiAtendido] = true;
    ChamadoMec[playerid][MecID] = id;
    pMecanico[id][SoliID] = playerid;
    pMecanico[id][AtendendoMec] = true;
    pMecanico[id][dada] = idx;

    GetVehiclePos(idx, Jisa[0], Jisa[1], Jisa[2]);

    format(Mensagem, sizeof(Mensagem), "Contato: {00BFFF}%s[%d]{FF4500}\nVe�culo Quebrado{FFFFFF}\nUse: /ConsertarVeiculo", PegarNick(playerid), playerid);
    pMecanico[id][MapID] = CreateDynamicMapIcon(Jisa[0], Jisa[1], Jisa[2], 27, -1, 0, 0, id, 99999.9, MAPICON_GLOBAL, -1);
    pMecanico[id][TextID] = CreateDynamic3DTextLabel(Mensagem, -1, 0.0, 0.0, 0.0, 16.0, INVALID_PLAYER_ID, idx, 0, 0, 0, id, 17.0, -1);
    ChamadoMec[playerid][MapID] = CreateDynamicMapIcon(Jisa[0], Jisa[1], Jisa[2], 27, -1, 0, 0, playerid, 99999.9, MAPICON_GLOBAL, -1);

    pMecanico[id][TimerMec] = SetTimerEx("AtualizarMecanico", 2500, true, "ddd", id, playerid, idx);

    SendClientMessage(id, 0xFFFF00FF, "| MEC�NICO | V� at� o local para efetuar o reparo do ve�culo");
    SendClientMessage(playerid, 0xFFFF00FF, "| MEC�NICO | O(A) Mec�nico est� a caminho para reparar seu ve�culo");
    return 1;
}

function AtualizarMecanico(id, playerid, idx)
{
    new Float:Jisa[3];
    GetVehiclePos(idx, Jisa[0], Jisa[1], Jisa[2]);

    DestroyDynamicMapIconEx(pMecanico[id][MapID]);
    DestroyDynamicMapIconEx(ChamadoMec[playerid][MapID]);

    pMecanico[id][MapID] = CreateDynamicMapIcon(Jisa[0], Jisa[1], Jisa[2], 27, -1, 0, 0, id, 99999.9, MAPICON_GLOBAL, -1);
    ChamadoMec[playerid][MapID] = CreateDynamicMapIcon(Jisa[0], Jisa[1], Jisa[2], 27, -1, 0, 0, playerid, 99999.9, MAPICON_GLOBAL, -1);
    return 1;
}

function ReparoVeiculoMec(playerid)
{
    KillTimer(pMecanico[playerid][TimerMec]);
    new id = pMecanico[playerid][SoliID],
        idx = pMecanico[playerid][dada],
        Mensagem[128];
    
    TogglePlayerControllable(playerid, 1);
    ClearAnimations(playerid, 1);
    SetPVarInt(playerid, "ASDASDASDADSADAS", 0);

    SetVehicleHealth(idx, 1000);
    RepairVehicle(idx);
    VeiculoServer[idx][vQuebrado] = false;

    DestroyDynamicMapIconEx(ChamadoMec[id][MapID]);
    DestroyDynamicMapIconEx(pMecanico[playerid][MapID]);
    DestroyDynamic3DTextLabelEx(pMecanico[playerid][TextID]);
    Jogador[playerid][Dinheiro] += GetPVarInt(playerid, "ASDASDASDSADA");
    Jogador[id][Dinheiro] -= GetPVarInt(playerid, "ASDASDASDSADA");

    pMecanico[playerid][AtendendoMec] = false;
    ChamadoMec[id][FuiAtendido] = false;

    format(Mensagem, sizeof(Mensagem), "| MEC�NICO | Voc� recebeu {32CD32}$%s{FFFFFF} pelo reparo do ve�culo", DinheiroSeparar(GetPVarInt(playerid, "ASDASDASDSADA")));
    SendClientMessage(playerid, -1, Mensagem);

    format(Mensagem, sizeof(Mensagem), "| MEC�NICO | O(A) Mec�nico(a) {00BFFF}%s[%d]{FFFFFF} fez o reparo do seu ve�culo", PegarNick(playerid), playerid);
    SendClientMessage(id, -1, Mensagem);
    return 1;
}

CMD:consertarveiculo(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Mec�nico")) return 0;
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode reparar");
    if(pMecanico[playerid][AtendendoMec] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� atendendo ningu�m");
    if(GetPVarInt(playerid, "ASDASDASDADSADAS") == 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� est� reparando um ve�culo");

    new Float:Jisa[3],
        idx = pMecanico[playerid][dada];
    GetVehiclePos(idx, Jisa[0], Jisa[1], Jisa[2]);
    if(!IsPlayerInRangeOfPoint(playerid, 5.0, Jisa[0], Jisa[1], Jisa[2])) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� longe do ve�culo");
    
    SetPVarInt(playerid, "ASDASDASDADSADAS", 1);

    TogglePlayerControllable(playerid, 0);
    ApplyAnimation(playerid, "BOMBER","BOM_Plant_Loop",4.0,1,0,0,1,0);
    CriarProgresso(playerid, "Reparando ve�culo, aguarde.", "ReparoVeiculoMec", 600);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    new id;
    if(ChamadoMec[playerid][FuiAtendido] == true)
    {
        id = ChamadoMec[playerid][MecID];
        KillTimer(pMecanico[id][TimerMec]);

        pMecanico[id][AtendendoMec] = false;
        if(GetPVarInt(id, "ASDASDASDADSADAS") == 1)
        {
            TogglePlayerControllable(id, 1);
            ClearAnimations(id, 1);
            PararProgresso(id);
        }

        DestroyDynamicMapIconEx(ChamadoMec[playerid][MapID]);
        DestroyDynamicMapIconEx(pMecanico[id][MapID]);
        DestroyDynamic3DTextLabelEx(pMecanico[id][TextID]);  
    }

    if(pMecanico[playerid][AtendendoMec] == true)
    {
        id = pMecanico[playerid][SoliID];
        KillTimer(pMecanico[playerid][TimerMec]);   

        ChamadoMec[id][FuiAtendido] = false;

        DestroyDynamicMapIconEx(ChamadoMec[id][MapID]);
        DestroyDynamicMapIconEx(pMecanico[playerid][MapID]);
        DestroyDynamic3DTextLabelEx(pMecanico[playerid][TextID]);  
    }
    if(pMecanico[playerid][MecanicoAlugado] == true) DestroyVehicleEx(pMecanico[playerid][MecanicoID]);

    new Aguazin[MecanicoInfo];
    pMecanico[playerid] = Aguazin;

    new Aguazain[ChamMec];
    ChamadoMec[playerid] = Aguazain;

    for(new i=0; i < MAX_PLAYERS; i++){
        MecQuery[playerid][i] = 0;
    }
    return 1;
}