#include <YSI_Coding\y_hooks>

CMD:contrato(playerid, params[])
{
    if(!strcmp(Jogador[playerid][Profissao], "Assassino")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode contratar um(a) jogador(a)");
    if(IsPolicia(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o para usar esse comando!");
    new id;
    if(sscanf(params, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Contrato [id]");
    if(id == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode se contratar!");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o conectado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o efetuou login");
    if(Jogador[id][Contratado] == true) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) j� est� em contrato de morte");
    if(Jogador[id][Admin] > 0 && pAdmin[id][FalsoPlayer] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode colocar um admin em contrato");
    if(IsPolicia(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode colocar um pol�cial em contrato");
    if(Jogador[playerid][Dinheiro] < 5000) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem $5.000 para fazer um contrato");

    Jogador[playerid][Dinheiro] -= 5000;
    Jogador[id][Contratado] = true;
    new Mensagem[228];
    format(Mensagem, sizeof(Mensagem), "| CONTRATO | O(A) Jogador(a) {FFFF00}%s[%d]{FFFFFF} colocou {B22222}%s[%d]{FFFFFF} em contrato, regi�o {FF4500}%s", PegarNick(playerid), playerid, PegarNick(id), id, GetPlayerZone(id));
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(strcmp(Jogador[i][Profissao], "Assassino")) continue;
        SendClientMessage(i, -1, Mensagem);
        PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
    }

    format(Mensagem, sizeof(Mensagem), "| CONTRATO | Voc� colocou contrato na cabe�a do(a) jogador(a) %s[%d]", PegarNick(id), id);
    SendClientMessage(playerid, 0xFF4500FF, Mensagem);
    return 1;
}

CMD:contratados(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Assassino") && Jogador[playerid][Admin] < 2) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o!");
    new Dialog[2500],
        Float:Disis,
        Float:Pss[3];
    strcat(Dialog, "Contratado(a)\tDist�ncia\n");
    GetPlayerPos(playerid, Pss[0], Pss[1], Pss[2]);

    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(Jogador[i][Contratado] == false) continue;
        if(Jogador[i][Admin] > 0 && pAdmin[i][FalsoPlayer] == false) continue;
        Disis = GetPlayerDistanceFromPoint(i, Pss[0], Pss[1], Pss[2]);
        strcatEx(Dialog, "{FFFFFF}%s[%d]\t\t{FFFF00}%0.2f\n", PegarNick(i), i, Disis);
    }
    Dialog_Show(playerid, SemFuncao, DIALOG_STYLE_TABLIST_HEADERS, "Contratados(as)", Dialog, "Fechar", "");
    return 1;
}

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
    if(pModo[playerid][Jogando] == true) return 1;
    if(strcmp(Jogador[playerid][Profissao], "Assassino")) return 1;
    if(Jogador[damagedid][Contratado] == false) return 1;
    if(bodypart != 9) return 1;
    if(GetPVarInt(playerid, "CalmaAss") > gettime()) return 1;
    SetPVarInt(playerid, "CalmaAss", gettime()+5);
    new Mensagem[128];

    SetPlayerHealth(damagedid, 0.0);

    format(Mensagem, sizeof(Mensagem), "| ASSASSINO | Voc� matou %s[%d] com um tiro na cabe�a", PegarNick(damagedid), damagedid);
    SendClientMessage(playerid, -1, Mensagem);
    format(Mensagem, sizeof(Mensagem), "| ASSASSINO | O(A) Assassino(a) %s[%d] lhe deu um tiro na cabe�a", PegarNick(playerid), playerid);
    SendClientMessage(damagedid, -1, Mensagem);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(Jogador[playerid][Contratado] == false) return 1;
    if(strcmp(Jogador[killerid][Profissao], "Assassino")) return 1;
    
    Jogador[killerid][Contratado] = false;
    new Mensagem[128];

    format(Mensagem, sizeof(Mensagem), "| CENTRAL | Assassinato na regi�o de %s, suspeito(a) %s[%d]", GetPlayerZone(playerid), PegarNick(killerid), killerid);
    for(new i=0; i < MAX_PLAYERS; i++){
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(!IsPolicia(i)) continue;
        if(pPolicia[i][PegouUniformePolicia] == false) continue;
        SendClientMessage(i, 0x4682B4FF, Mensagem);
    }

    new MrM = random(3400-1900)+1900;
    Jogador[killerid][Dinheiro] += MrM;

    format(Mensagem, sizeof(Mensagem), "| ASSASSINO | Voc� recebeu {32CD32}$%s{FFFFFF} por matar %s", DinheiroSeparar(MrM), PegarNick(playerid));
    SendClientMessage(killerid, -1, Mensagem);

    Jogador[killerid][Estrelas] += 6;
    Jogador[playerid][Contratado] = false;
    return 1;
}