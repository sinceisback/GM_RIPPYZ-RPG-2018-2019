function MaconhaPlantio(playerid, id, processo, bool:Adbu)
{

    // Processo de Crescimento
    if(processo == 1)
    {
        // Gambiarras
        new bool:BostAcbou = false,
            Mensagem[400];

        // Adicionar um Progresdso com boost
        if(Adbu == true)
        {
            Plantador[playerid][id][ProgressoPlantio]++;   
            Plantador[playerid][id][AbudoUsado]++;
            if(Plantador[playerid][id][AbudoUsado] >= 25) BostAcbou = true;
        }
        Plantador[playerid][id][ProgressoPlantio]++;
        if(Plantador[playerid][id][ProgressoPlantio] > 100) Plantador[playerid][id][ProgressoPlantio] = 100;


        // Adicionar um sistema de �gua
        if(Adbu == false)
        {
            if(Plantador[playerid][id][ProximaRegada] == 0 && Plantador[playerid][id][ProgressoPlantio] <= 80 && Plantador[playerid][id][AnularReg] == false)
            {
                Plantador[playerid][id][ProximaRegada] = Plantador[playerid][id][ProgressoPlantio]+random(100+2)-2;
                if(Plantador[playerid][id][ProximaRegada] >= 100) Plantador[playerid][id][ProximaRegada] = 97;
            }
        }

        // Verificar se j� acabou
        if(Plantador[playerid][id][ProgressoPlantio] >= 100)
        {
            KillTimer(Plantador[playerid][id][PlantioTempo]);
            Plantador[playerid][id][PlantioTempo] = SetTimerEx("MaconhaPlantio", 1000, true, "dddd", playerid, id, 3, false);
            //Plantador[playerid][id][ProgressoPlantio];
            Plantador[playerid][id][TempoPerca] = 120;
            
            format(Mensagem, sizeof(Mensagem), "| MUDA | Sua muda ({FF4500}ID: %d{FFFFFF}) est� pronta para colheita", id);
            SendClientMessage(playerid, -1, Mensagem);

            format(Mensagem, sizeof(Mensagem), "Planta��o %s[%d] ID: %d\nProgresso: {FF0000}%d\n{FFFF00}Pronta para colheita!", PegarNick(playerid), playerid, id, Plantador[playerid][id][ProgressoPlantio]);
            UpdateDynamic3DTextLabelText(Plantador[playerid][id][TextoPlantio], -1, Mensagem); 
            return 1;
        }

        // Se o boost j� acabou voltar para o normal
        if(BostAcbou == true)
        {
            KillTimer(Plantador[playerid][id][PlantioTempo]);
            Plantador[playerid][id][PlantioTempo] = SetTimerEx("MaconhaPlantio", 3000, true, "dddd", playerid, id, 1, false); 
            SendClientMessage(playerid, -1, "| ATEN��O | O Adubo de uma das suas sementes acabou");
            return 1;
        }

        // Sistema para verificar se precisa de �gua
        if(Plantador[playerid][id][ProximaRegada] > 0 && Plantador[playerid][id][ProximaRegada] == Plantador[playerid][id][ProgressoPlantio] && Adbu == false)
        {
            KillTimer(Plantador[playerid][id][PlantioTempo]);
            Plantador[playerid][id][PlantioTempo] = SetTimerEx("MaconhaPlantio", 2000, true, "dddd", playerid, id, 2, false); 
            format(Mensagem, sizeof(Mensagem), "Planta��o %s[%d] ID: %d\nProgresso: {FF0000}%d\n{00BFFF}Precisa de �gua!", PegarNick(playerid), playerid, id, Plantador[playerid][id][ProgressoPlantio]);
            UpdateDynamic3DTextLabelText(Plantador[playerid][id][TextoPlantio], -1, Mensagem);

            format(Mensagem, sizeof(Mensagem), "| MUDA | Sua muda ({FF4500}ID: %d{FFFFFF}) est� precisando de �gua", id);
            SendClientMessage(playerid, -1, Mensagem);
            return 1;
        } 

        // Atualizar Progresso
        if(Adbu == false)
        {
            format(Mensagem, sizeof(Mensagem), "Planta��o %s[%d] ID: %d\nProgresso: {FF0000}%d", PegarNick(playerid), playerid, id, Plantador[playerid][id][ProgressoPlantio]);
            UpdateDynamic3DTextLabelText(Plantador[playerid][id][TextoPlantio], -1, Mensagem);
        }
        else
        {
            format(Mensagem, sizeof(Mensagem), "Planta��o %s[%d] ID: %d\nProgresso: {FF0000}%d\n{00BFFF}Com Adubo", PegarNick(playerid), playerid, id, Plantador[playerid][id][ProgressoPlantio]);
            UpdateDynamic3DTextLabelText(Plantador[playerid][id][TextoPlantio], -1, Mensagem);
        }
    }

    // Procesos de �gua
    else if(processo == 2)
    {
        new Mensagem[400];
        Plantador[playerid][id][AguaPrecisa]++;
        if(Plantador[playerid][id][AguaPrecisa] >= 100)
        {
            format(Mensagem, sizeof(Mensagem), "| PLANTA��O | Voc� perdeu uma muda (ID: %d) por falta de �gua", id);
            AcabarComPlantio(playerid, id);
            SendClientMessage(playerid, 0xFF4500FF, Mensagem);
            return 1;
        }

        // Atualizar
        format(Mensagem, sizeof(Mensagem), "Planta��o %s[%d] ID: %d\nProgresso: {FF0000}%d\n{00BFFF}Precisa de �gua{FFFFFF}\nTempo: {FF4500}%d/100", PegarNick(playerid), playerid, id, Plantador[playerid][id][ProgressoPlantio], Plantador[playerid][id][AguaPrecisa]);
        UpdateDynamic3DTextLabelText(Plantador[playerid][id][TextoPlantio], -1, Mensagem);
    }

    // Processo de Colheita
    else if(processo == 3)
    {
        new Mensagem[400];
        Plantador[playerid][id][TempoPerca]--;      
        if(Plantador[playerid][id][TempoPerca] <= 0)
        {
            format(Mensagem, sizeof(Mensagem), "| PLANTA��O | Voc� perdeu uma muda (ID: %d) por falta de colheita", id);
            AcabarComPlantio(playerid, id);
            SendClientMessage(playerid, 0xFFFF00FF, Mensagem);
            return 1;
        }
        format(Mensagem, sizeof(Mensagem), "Planta��o %s[%d] ID: %d\nProgresso: {FF0000}%d\n{FFFF00}Colheita Pronta!{FFFFFF}\nTempo: {FF4500}%s", PegarNick(playerid), playerid, id, Plantador[playerid][id][ProgressoPlantio], SegundosParaMinutosEx(Plantador[playerid][id][TempoPerca]));
        UpdateDynamic3DTextLabelText(Plantador[playerid][id][TextoPlantio], -1, Mensagem);
    }

    return 1;
}


CMD:plantar(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Plantador de Maconha")) return 0;
    if(Jogador[playerid][Sementes] <= 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem sementes, compre no beco ( /beco )");
    if(Jogador[playerid][Vasos] <= 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem vasos, compre no beco ( /beco )");
    //if(Jogador[playerid][Sacos] <= 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem sacos, compre na loja de utili�rios");
    if(PlantioID(playerid) == -1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� precisa colher outra semente para plantar essa semente");
    if(!IsPlayerInDynamicArea(playerid, MensagemArea)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� na planta��o");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode plantar em um ve�culo");
    if(GetPlayerSpeed(playerid) > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� precisa estar parado para plantar");
    for(new i=0; i < 10; i++)
    {
        if(Plantador[playerid][i][Plantado] == false) continue;
        if(IsPlayerInRangeOfPoint(playerid, 2.0, Plantador[playerid][i][PlantioX], Plantador[playerid][i][PlantioY], Plantador[playerid][i][PlantioZ])) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode plantar muito perto de outra!");
    }

    new Mensagem[300],
        id = PlantioID(playerid),
        Float:plPos[3];

    if(id == 0){
        if(Jogador[playerid][Agua] < 10) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem �gua sucifiente, compre na loja de utili�rios");
    }
    GetPlayerPos(playerid, plPos[0], plPos[1], plPos[2]);
    format(Mensagem, sizeof(Mensagem), "Planta��o %s[%d] ID: %d\nProgresso: {FF0000}%d", PegarNick(playerid), playerid, id, Plantador[playerid][id][ProgressoPlantio]);

    // Adicionar informa��es no ch�o
    Plantador[playerid][id][PlantaObj] = CreateDynamicObject(2195, plPos[0], plPos[1], plPos[2]-1, 00.0, 00.0, 0.0, 0, 0,-1, 300.0, 300.0);
    Plantador[playerid][id][TextoPlantio] = CreateDynamic3DTextLabel(Mensagem, -1, plPos[0], plPos[1], plPos[2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 10.0);
    Plantador[playerid][id][IconePlantio] = CreateDynamicMapIcon(plPos[0], plPos[1], plPos[2], 56, -1, 0, 0, playerid, 150.0, MAPICON_LOCAL, MensagemArea);
    KillTimer(Plantador[playerid][id][PlantioTempo]);
    Plantador[playerid][id][PlantioTempo] = SetTimerEx("MaconhaPlantio", 3000, true, "dddd", playerid, id, 1, false); 

    Plantador[playerid][id][PlantioX] = plPos[0];
    Plantador[playerid][id][PlantioY] = plPos[1];
    Plantador[playerid][id][PlantioZ] = plPos[2];
    Plantador[playerid][id][Plantado] = true;

    Jogador[playerid][Vasos]--;
    Jogador[playerid][Sementes]--;

    TogglePlayerControllable(playerid, 0);
    ApplyAnimation(playerid, "BOMBER","BOM_Plant_Loop",4.0,1,0,0,1,0);
    SetTimerEx("LimparPlantAnim", 3000, false, "d", playerid);
    format(Mensagem, sizeof(Mensagem), "| PLANTA��O | Voc� plantou uma semente ( Vaso: {FFFF00}%d{FFFFFF} / Semente: {FF0000}%d{FFFFFF} )", Jogador[playerid][Vasos], Jogador[playerid][Sementes]);
    SendClientMessage(playerid, -1, Mensagem);
    return 1;
}

CMD:colher(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Plantador de Maconha")) return 0;
    if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar esse comando em um ve�culo");
    new bool:PertoN = false,
        cc = 0;
    for(new i=0; i < 10; i++)
    {
        if(Plantador[playerid][i][Plantado] == false) continue;
        cc++;
        if(!IsPlayerInRangeOfPoint(playerid, 1.0, Plantador[playerid][i][PlantioX], Plantador[playerid][i][PlantioY], Plantador[playerid][i][PlantioZ])) continue;
        PertoN = true;
        if(Plantador[playerid][i][TempoPerca] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa muda n�o est� pronta para colheita");
        AcabarComPlantio(playerid, i);
        
        new dasda = random(1300-700)+700,
            Mensagem[128];
        format(Mensagem, sizeof(Mensagem), "| PLANTA��O | Voc� colheu uma muda e recebeu {32CD32}$%s", DinheiroSeparar(dasda));
        SendClientMessage(playerid, -1, Mensagem);
        Jogador[playerid][Dinheiro] += dasda;
        if(random(100) > 49) Jogador[playerid][Estrelas] += random(3-2)+2;
        //Plantador[playerid][i][ColheuEntrega] = true;
        //SendClientMessage(playerid, 0xFFFF00FF, "| INFO | Voc� precisa ir at� a boca de fumo para entregar");
        break;
    }
    if(cc == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem nenhuma semente muda");
    else if(PertoN == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� perto de nenhuma muda");
    return 1;
}

CMD:regar(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Plantador de Maconha")) return 0;
    if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar esse comando em um ve�culo");
    new bool:PertoN = false,
        cc = 0;
    for(new i=0; i < 10; i++)
    {
        if(Plantador[playerid][i][Plantado] == false) continue;
        cc++;
        if(!IsPlayerInRangeOfPoint(playerid, 1.0, Plantador[playerid][i][PlantioX], Plantador[playerid][i][PlantioY], Plantador[playerid][i][PlantioZ])) continue;
        PertoN = true;
        if(Jogador[playerid][Agua] <= 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem �guas!");
        if(Plantador[playerid][i][TempoPerca] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� precisa colher essa muda");
        if(Plantador[playerid][i][AguaPrecisa] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa muda n�o precisa de �gua");
        new Mensagem[300];
        Plantador[playerid][i][AnularReg] = true; // Bloquear que pe�a �gua novamente
        KillTimer(Plantador[playerid][i][PlantioTempo]);
        Plantador[playerid][i][PlantioTempo] = SetTimerEx("MaconhaPlantio", 3000, true, "dddd", playerid, i, 1, false); 
        Plantador[playerid][i][AguaPrecisa] = 0;
        Plantador[playerid][i][ProximaRegada] = 0;
        
        Jogador[playerid][Agua]--;
        TogglePlayerControllable(playerid, 0);
        ApplyAnimation(playerid, "BOMBER","BOM_Plant_Loop",4.0,1,0,0,1,0);
        SetTimerEx("LimparPlantAnim", 3000, false, "d", playerid);
        format(Mensagem, sizeof(Mensagem), "| MUDA | Voc� regou uma muda ({00BFFF}ID: %d{FFFFFF}) - �gua(s) Restante(s): {FF4500}%d", i, Jogador[playerid][Agua]);
        SendClientMessage(playerid, -1, Mensagem);

        break;
    }
    if(cc == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem nenhuma semente muda");
    else if(PertoN == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� perto de nenhuma muda");
    return 1;
}

CMD:adubo(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Plantador de Maconha")) return 0;
    if(IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar esse comando em um ve�culo");
    new bool:PertoN = false,
        cc = 0;
    for(new i=0; i < 10; i++)
    {
        if(Plantador[playerid][i][Plantado] == false) continue;
        cc++;
        if(!IsPlayerInRangeOfPoint(playerid, 1.0, Plantador[playerid][i][PlantioX], Plantador[playerid][i][PlantioY], Plantador[playerid][i][PlantioZ])) continue;
        PertoN = true;
        if(Plantador[playerid][i][TempoPerca] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� precisa colher essa muda");
        if(Plantador[playerid][i][UsouAdubo] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Essa muda j� usou adubo uma vez");
        if(Jogador[playerid][Adubos] <= 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o possui mais adubos!");
        new Mensagem[128];
        Plantador[playerid][i][UsouAdubo] = true;
        Jogador[playerid][Adubos]--;
        KillTimer(Plantador[playerid][i][PlantioTempo]);
        Plantador[playerid][i][PlantioTempo] = SetTimerEx("MaconhaPlantio", 1000, true, "dddd", playerid, i, 1, true); 
        format(Mensagem, sizeof(Mensagem), "| MUDA | Voc� usou adubo nessa muda ( Restante: {FF0000}%d{FFFFFF} )", Jogador[playerid][Adubos]);
        SendClientMessage(playerid, -1, Mensagem);
        TogglePlayerControllable(playerid, 0);
        ApplyAnimation(playerid, "BOMBER","BOM_Plant_Loop",4.0,1,0,0,1,0);
        SetTimerEx("LimparPlantAnim", 3000, false, "d", playerid);
        break;
    }
    if(cc == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem nenhuma semente muda");
    else if(PertoN == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� perto de nenhuma muda");
    return 1;
}

Dialog:PlantacaoFuncao(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    new dasda;
    for(new i=0; i < 10; i++)
    {
        if(Plantador[playerid][i][ColheuEntrega] == false) continue;
        Plantador[playerid][i][ColheuEntrega] = false;
        dasda++;
    }
    if(dasda == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem drogas com s� da planta��o");
    new PrecoX = 750*dasda,
        Mensagem[128];
    MaconhaUnd += dasda;
    Jogador[playerid][Estrelas] += random(6-5)+5;
    Jogador[playerid][Dinheiro] += PrecoX;
    format(Mensagem, sizeof(Mensagem), "| TR�FICO | Voc� entregou {FFA500}%d{FFFFFF} droga(s) e recebeu {32CD32}$%s", dasda, DinheiroSeparar(PrecoX));
    SendClientMessage(playerid, -1, Mensagem);
    return 1;
}