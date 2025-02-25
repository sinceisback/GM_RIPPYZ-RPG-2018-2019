#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    CreateDynamic3DTextLabel("{00BFFF}Uber\n{FFFFFF}Aperte {CCCCCC}'Y'{FFFFFF} para alugar/devolver", -1, 2240.4692,2048.6892,11.0625, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0,  0, -1);
    CreateDynamicPickup(1239, 1, 2240.4692,2048.6892,11.0625, 0, 0, -1, 50.0);

    CreateDynamic3DTextLabel("{00BFFF}Uber\n{FFFFFF}Aperte {CCCCCC}'Y'{FFFFFF} para pegar seu uniforme", -1, 2262.3628,2043.2555,10.8203, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0,  0, -1);
    CreateDynamicPickup(1239, 1, 2262.3628,2043.2555,10.8203, 0, 0, -1, 50.0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys != KEY_YES) return 1;
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;

    //Veiculo
    if(IsPlayerInRangeOfPoint(playerid, 3.0, 2240.4692,2048.6892,11.0625))
    {
        if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return 1;
        if(strcmp(Jogador[playerid][Profissao], "Uber")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
        if(pUber[playerid][UberAtendeu] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� ainda n�o concluiu uma corrida");
        if(GetPVarInt(playerid, "AntiUberFloodCarro") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco.");
        if(pUber[playerid][UberPegouVeiculo] == true)
        {
            DestroyVehicleEx(pUber[playerid][UberVeiculo]);
            VerificarMarcao(playerid);
            pUber[playerid][UberPegouVeiculo] = false;
            SendClientMessage(playerid, 0xFFFF00FF, "| UBER | Ve�culo devolvido para HQ");
            SetPVarInt(playerid, "AntiUberFloodCarro", gettime()+5);
            return 1;
        }
        if(pUber[playerid][UberPegouUniforme] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� com seu uniforme");
        if(Jogador[playerid][CarteiraB] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o possui CNH para alugar um carro ( Habilita��o: B )");
        new rid = random(sizeof(UberPosVeh));
        pUber[playerid][UberVeiculo] = CreateVehicleEx(playerid, 421, UberPosVeh[rid][UberPosX], UberPosVeh[rid][UberPosY], UberPosVeh[rid][UberPosZ], UberPosVeh[rid][UberPosA], 0, 0, -1, 0);
        VeiculoServer[pUber[playerid][UberVeiculo]][Tranca] = 1; //Deixar ve�culo trancado
        pUber[playerid][UberPegouVeiculo] = true;
        
        // Marca��o
        MarcarPosicao(playerid, UberPosVeh[rid][UberPosX], UberPosVeh[rid][UberPosY], UberPosVeh[rid][UberPosZ]);
        
        SetPVarInt(playerid, "AntiUberFloodCarro", gettime()+5);
        SendClientMessage(playerid, 0xFFFF00FF, "| UBER | Seu ve�culo foi alugado com sucesso!");
    }


    else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2262.3628,2043.2555,10.8203) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
    {
        if(strcmp(Jogador[playerid][Profissao], "Uber")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
        if(pUber[playerid][UberAtendeu] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� ainda n�o concluiu uma corrida");
        if(GetPVarInt(playerid, "AntiUberFloodUniforme") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco.");
        if(pUber[playerid][UberPegouUniforme] == true)
        {
            if(pUber[playerid][UberPegouVeiculo] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Devolva seu ve�culo antes de remover o uniforme");
            pUber[playerid][UberPegouUniforme] = false;
            SetPlayerSkin(playerid, Jogador[playerid][Skin]);
            Jogador[playerid][SkinProfissao] = -1;
            Jogador[playerid][Trabalhando] = false;
            SendClientMessage(playerid, 0xFFFF00FF, "| UBER | Voc� removeu seu uniforme");
            SetPVarInt(playerid, "AntiUberFloodUniforme", gettime()+5);
            return 1;
        }
        Jogador[playerid][Trabalhando] = true;
        pUber[playerid][UberPegouUniforme] = true;
        if(Jogador[playerid][Sexo] == 1){
            SetPlayerSkin(playerid, 147);
            Jogador[playerid][SkinProfissao] = 147;
        }
        else if(Jogador[playerid][Sexo] == 2){
            SetPlayerSkin(playerid, 141);
            Jogador[playerid][SkinProfissao] = 141;   
        }
        SendClientMessage(playerid, 0xFFFF00FF, "| UBER | Voc� pegou seu uniforme");
        SetPVarInt(playerid, "AntiUberFloodUniforme", gettime()+5);
    }

    return 1;
}

CMD:aceitar(playerid, params[])
{
    if(strcmp(Jogador[playerid][Profissao], "Uber")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    new id;
    if(sscanf(params, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Aceitar [ID]");
    if(pUber[playerid][UberPegouUniforme] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pegou seu uniforme");
    if(pUber[playerid][UberPegouVeiculo] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pegou seu ve�culo");
    if(GetPlayerVehicleID(playerid) != pUber[playerid][UberVeiculo]) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� em seu ve�culo alugado");
    if(pUber[playerid][UberAtendeu] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� j� aceitou um chamado");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o foi encontrado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o foi encontrado(a)");
    if(pUber[id][Chamada] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o solicitou uber");
    if(pUber[id][StatusChamado] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) j� foi atendido(a)");
    if(id == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode aceitar seu pedido");

    //Passageiro
    pUber[id][StatusChamado] = 1;
    pUber[id][UberID] = playerid;

    //Motorista
    pUber[playerid][UberAtendeu] = true;
    pUber[playerid][PassageiroID] = id;

    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "| UBER | {FF4500}%s[%d]{FFFFFF} aceitou seu chamado", PegarNick(playerid), playerid);
    SendClientMessage(id, -1, Mensagem);

    format(Mensagem, sizeof(Mensagem), "| UBER | Voc� aceitou o chamado do(a) {FF4500}%s[%d]", PegarNick(id), id);
    SendClientMessage(playerid, -1, Mensagem);

    SendClientMessage(id, 0xFF4500FF, "| AVISO | Voc� pode cancelar acessando seu celular e cancelando por l�");
    SendClientMessage(playerid, 0xFF4500FF, "| AVISO | Voc� pode cancelar usando /cancelar");

    new Float:moPos[3],
        Float:poPos[3]
    ;
    GetPlayerPos(id, poPos[0], poPos[1], poPos[2]);
    GetPlayerPos(playerid, moPos[0], moPos[1], moPos[2]);

    pUber[playerid][UberIcone] = CreateDynamicMapIcon(poPos[0], poPos[1], poPos[2], 58, -1, 0, 0, playerid, 99999.0, MAPICON_GLOBAL);
    pUber[id][UberIcone] = CreateDynamicMapIcon(moPos[0], moPos[1], moPos[2], 55, -1, 0, 0, id, 99999.0, MAPICON_GLOBAL);
    pUber[playerid][UberTemporizador] = SetTimerEx("AtualizarUber", 2000, true, "d", playerid);
    return 1;
}