#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys == KEY_YES)
    {
        // Spawnar um ve�culo de mec�nico
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 313.2029,-18.0681,1.5781))
        {
            if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return 1;
            if(strcmp(Jogador[playerid][Profissao], "Mec�nico")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
            if(GetPVarInt(playerid, "ASDASDASDASDA") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco.");
            if(pMecanico[playerid][AtendendoMec] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� com um servi�o");
            if(pMecanico[playerid][MecanicoAlugado] == false)
            {
                if(Jogador[playerid][CarteiraC] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o possui CNH para alugar um carro ( Habilita��o: C )");
                new sidd = random(sizeof(mSpawn));
                pMecanico[playerid][MecanicoID] = CreateVehicleEx(playerid, 525, mSpawn[sidd][cMX], mSpawn[sidd][cMY], mSpawn[sidd][cMZ], mSpawn[sidd][cMA], 4, 4, -1, 0);
                VeiculoServer[pMecanico[playerid][MecanicoID]][Tranca] = 1;
                MarcarPosicao(playerid, mSpawn[sidd][cMX], mSpawn[sidd][cMY], mSpawn[sidd][cMZ]);
                pMecanico[playerid][MecanicoAlugado] = true;
                Jogador[playerid][Trabalhando] = true;
                SetPVarInt(playerid, "ASDASDASDASDA", gettime()+10);
                SendClientMessage(playerid, 0xFFFF00FF, "| MEC�NICA | Seu ve�culo foi colocado atr�s da mec�nica");
                return 1;
            }

            if(IsTrailerAttachedToVehicle(pMecanico[playerid][MecanicoID])){
   				DetachTrailerFromVehicle(pMecanico[playerid][MecanicoID]);
   			}

            VerificarMarcacao(playerid);
            SetPVarInt(playerid, "ASDASDASDASDA", gettime()+10);
            pMecanico[playerid][MecanicoAlugado] = false;
            Jogador[playerid][Trabalhando] = false;
            DestroyVehicleEx(pMecanico[playerid][MecanicoID]);
            SendClientMessage(playerid, 0xFFFF00FF, "| MEC�NICA | Voc� devolveu o ve�culo para mec�nica");
        }
    }


    // Sistema de Rebocar
    if(newkeys == KEY_CTRL_BACK && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
        if(GetPlayerVirtualWorld(playerid) != 0) return 1;
        if(strcmp(Jogador[playerid][Profissao], "Mec�nico")) return 1;
	    if(pMecanico[playerid][MecanicoAlugado] == false) return 1;
        if(GetPlayerVehicleID(playerid) != pMecanico[playerid][MecanicoID]) return 1;

        if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid))){
   			DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
            return 1;
   		}

	    // SendClientMessage(playerid, 0xFFFF00FF, "| INFO | Tentando rebocar o ve�culo");

		new Float:pX, Float:pY, Float:pZ,
            Float:vX, Float:vY, Float:vZ;
		GetPlayerPos(playerid, pX, pY, pZ);
        for(new i=0; i < MAX_VEHICLES; i++)
        {
            if(GetPlayerVehicleID(playerid) == i) continue;
            GetVehiclePos(i, vX, vY, vZ);
            if(floatabs(pX-vX) < 5.0 && floatabs(pY-vY) < 5.0 && floatabs(pZ-vZ) < 5.0)
   			{
                if(IsVehicleOccupied(i)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse ve�culo tem um(a) motorista");
   				if(!IsApenasCarro(GetVehicleModel(i))) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode rebocar");
                AttachTrailerToVehicle(i, GetPlayerVehicleID(playerid));
   				SendClientMessage(playerid, 0xFFFF00FF, "| INFO | Voc� rebocou um ve�culo");
                break;
            }
        }
	}

    return 1;
}