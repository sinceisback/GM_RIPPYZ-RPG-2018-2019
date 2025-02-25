#include <YSI_Coding\y_hooks>

new Fancic;
hook OnGameModeInit()
{
    Fancic = CreateDynamicCP(249.2837,67.9806,1003.6406, 1.0, 1300, 6, -1, 16.0, -1);
    return 1;
}

Dialog:CadeiaSoltar(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(isnull(inputtext)) return 1;
    new id;
    if(sscanf(inputtext, "d", id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� colocou um ID inv�lido");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o conectado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o logado(a)");
    if(Jogador[id][Preso] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o est� preso(a)");
    if(Jogador[id][CadeiaEstilo] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o pode pagar fian�as desse(a) jogador(a)");
    if(Jogador[playerid][Dinheiro] < DinheiroPrisao(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem dinheiro sucifiente");

    Jogador[playerid][Dinheiro] -= DinheiroPrisao(id);
    EnviarLogDinheiro(playerid, id, DinheiroPrisao(playerid), "Fian�a Request");

    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "| FIAN�A | Voc� pagou $%s para soltar %s[%d]", DinheiroSeparar(DinheiroPrisao(id)), PegarNick(id), id);
    SendClientMessage(playerid, 0x1E90FFFF, Mensagem);

    format(Mensagem, sizeof(Mensagem), "| FIAN�A | %s[%d] pagou para retirar voc� da pris�o", PegarNick(playerid), playerid);
    SendClientMessage(id, 0x1E90FFFF, Mensagem);

    RemoverDaCadeia(id);
    Jogador[id][Preso] = 0;
    return 1;
}

Dialog:FiancaMenu(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem)
    {
        case 0: Dialog_Show(playerid, CadeiaSoltar, DIALOG_STYLE_INPUT, "{FF0000}Fian�a", "Coloque abaixo o ID do preso(a)", "Pagar", "Fechar");
        case 1: MostrarPresos(playerid);
        case 2: MostrarProcurados(playerid);
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, checkpointid)
{
    if(checkpointid != Fancic) return 1;

    new Dialog[128];
    strcat(Dialog, "Pagar Fian�a\n");
    strcat(Dialog, "Lista de Presos\n");
    strcat(Dialog, "{FF0000}Lista de Procurados");
    Dialog_Show(playerid, FiancaMenu, DIALOG_STYLE_TABLIST, "{FF0000}Departamento de Pol�cia", Dialog, "Selecionar", "Fechar");
    return 1;
}