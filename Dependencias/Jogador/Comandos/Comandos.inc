#include <YSI_Coding\y_hooks>

new DelayDuvida[MAX_PLAYERS];
new DelayDuvidaVip[MAX_PLAYERS];

new DelayAjuda[MAX_PLAYERS];
new DelayAjudaVip[MAX_PLAYERS];

new ReporteDelay[MAX_PLAYERS];

CMD:admins(playerid)
{
    //if(Jogador[playerid][Admin] < 1) return 0;
    new Lista[900];
    new Contador = 0;
    strcat(Lista, "Admin\tCargo\tStatus\n");
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Admin] < 1) continue;
        if(pAdmin[i][Camuflado] == true && Jogador[playerid][Admin] > 1)
        {
            strcatEx(Lista, "%s\t%s\t{DC143C}Camuflado(a)\n", PegarNick(i), CargoAdmin(1, i)); 
            Contador++; 
        }
        else if(pAdmin[i][Camuflado] == false)
        {
            strcatEx(Lista, "%s\t%s\t{00FF00}Online\n", PegarNick(i), CargoAdmin(1, i));
            Contador++;   
        }
    }

    new Teste[128];
    format(Teste, sizeof(Teste), "Administrador(es): {00FA9A}%d", Contador);
    if(Contador > 0) Dialog_Show(playerid, AdminsOnline, DIALOG_STYLE_TABLIST_HEADERS, Teste, Lista, "Confirmar", #);  
    else Dialog_Show(playerid, AdminsOnline, DIALOG_STYLE_MSGBOX, Teste, "{FF0000}N�o h� administradores online nesse momento!", "Fechar", #); 
    return 1;
}

CMD:duvida(playerid, params[])
{
    if(Jogador[playerid][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar esse comando!");
    new Mensagem[90];
    if(sscanf(params, "s[90]", Mensagem)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Duvida [Mensagem]");
    if(strlen(Mensagem) > 55) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Mensagem muito longa!");

    new DuvidaMensagem[300],
        Contador = 0,
        bool:VipVerificacao = false;

    if(Jogador[playerid][Vip] > gettime()){
        if(DelayDuvidaVip[playerid] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | D�vida VIP est� congestionada, aguarde um pouco.");
        format(DuvidaMensagem, sizeof(DuvidaMensagem), "| D�VIDA-VIP | O(A) Jogador(a) {FF8C00}%s[%d]{FFFFFF} perguntou ( {e82741}%s{FFFFFF} )", PegarNick(playerid), playerid, Mensagem);
        VipVerificacao = true;
    }
    else{
        if(DelayDuvida[playerid] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | D�vida est� congestionada, aguarde um pouco.");
        format(DuvidaMensagem, sizeof(DuvidaMensagem), "| D�VIDA | O(A) Jogador(a) {FF8C00}%s[%d]{FFFFFF} perguntou ( {ff1232}%s{FFFFFF} )", PegarNick(playerid), playerid, Mensagem);
    }


    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Admin] < 1) continue;
        SendClientMessage(i, -1, DuvidaMensagem);
        Contador++;
    }  
 
    if(Contador > 0){
        SendClientMessage(playerid, -1, "| D�VIDA | Sua d�vida foi enviada com sucesso!");
        if(VipVerificacao == true) DelayDuvidaVip[playerid] = gettime()+60;
        else DelayDuvida[playerid] = gettime()+65;
    }
    else SendClientMessage(playerid, -1, "| ERRO | N�o h� administradores, sua d�vida n�o foi enviada.");
    return 1;
}

CMD:bug(playerid, params[])
{
    new Mensagem[128];
    if(sscanf(params, "s[128]", Mensagem)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /bug [Pedido de Ajuda]");
    if(strlen(Mensagem) > 80) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Seu pedido de ajuda est� muito grande!");
    
    new HelpMensagem[300],
        Contador = 0,
        bool:VipVerificacao = false;

    if(Jogador[playerid][Vip] > gettime()){
        if(DelayAjudaVip[playerid] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco antes de enviar!");
        format(HelpMensagem, sizeof(HelpMensagem), "| BUG-VIP | O(A) Jogador(a) {FF8C00}%s[%d]{FFFFFF} est� pedindo ajuda ( {7221ff}%s{FFFFFF} )", PegarNick(playerid), playerid, Mensagem);
        VipVerificacao = true;
    }
    else
    {
        if(DelayAjuda[playerid] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco antes de enviar!");
        format(HelpMensagem, sizeof(HelpMensagem), "| BUG | O(A) Jogador(a) {FF8C00}%s[%d]{FFFFFF} est� pedindo ajuda ( {9457ff}%s{FFFFFF} )", PegarNick(playerid), playerid, Mensagem);
    }

    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Admin] < 1) continue;
        SendClientMessage(i, -1, HelpMensagem);
        Contador++;
    }  
 
    if(Contador > 0)
    {
        SendClientMessage(playerid, -1, "| BUG | Seu pedido de ajuda foi enviado com sucesso!");
        if(VipVerificacao == true) DelayAjudaVip[playerid] = gettime()+20;
        else DelayAjuda[playerid] = gettime()+30;
    }
    else SendClientMessage(playerid, -1, "| ERRO | N�o h� administradores online no momento, seu pedido de ajuda foi cancelado");
    return 1;
}

CMD:relatorio(playerid, params[])
{
    if(Jogador[playerid][Admin] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar esse comando!");
    new id, relatorio[228];
    if(sscanf(params, "ds[128]", id, relatorio)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Relatorio [ID] [Motivo]");
    if(id == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode se reportar!");
    if(Jogador[id][Admin] > 0 && pAdmin[id][FalsoPlayer] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode reportar um membro da equipe!");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o encontrado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o logado(a)!");
    if(ReporteDelay[playerid] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Aguarde um pouco.");
    if(strlen(relatorio) > 50) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Seu relat�rio est� muito longo");

    new MensagemRelatorio[300];
    new Contador = 0;

    ReporteDelay[playerid] = gettime()+30;

    format(MensagemRelatorio, sizeof(MensagemRelatorio), "| RELAT�RIO | O(A) Jogador(a) {FF0000}%s[%d]{FFFFFF} reportou {FF0000}%s[%d]{FFFFFF} ( Motivo: {f27522}%s{FFFFFF} )", PegarNick(playerid), playerid, PegarNick(id), id, relatorio);
    for(new i; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Admin] < 2) continue;
        SendClientMessage(i, -1, MensagemRelatorio);
        Contador++;  
    }

    if(Contador > 0) SendClientMessage(playerid, -1, "| RELAT�RIO | Seu relat�rio foi enviado com sucesso");
    else SendClientMessage(playerid, 0xFF4500FF, "| ERRO | N�o h� administradores online no momento");
    return 1;
}

CMD:creditos(playerid)
{
    new Dialog[800];
    strcat(Dialog, "\t\tAgradecimentos\n\n");
    strcat(Dialog, "{FFFFFF}Kettler e LinzYh ( {FF4500}Constru��es no Mapa{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Nelson ( {FF4500}Ajuda na organiza��o do c�digo{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Isabella ( {FF4500}Prote��o contra cheaters{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Masked ( {FF4500}Template do Email{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Foolish ( {FF4500}Corre��es no Mysql{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Paulo e MichaelS ( {FF4500}Adicionarem casas/empresas pelo Servidor{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Cowboy ( {FF4500}Posicionamento de c�meras nas concession�rias{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Kannario ( {FF4500}Assessoria de comunica��o{FFFFFF} )\n");
    strcat(Dialog, "{FFFFFF}Klaus, Desper e MarcosL ( {FF4500}Por reportar problemas no beta/desenvolvimento{FFFFFF} )\n\n");
    strcat(Dialog, "{FFFFFF}( Servidor desenvolvido e fundado por {00BFFF}blueN{FFFFFF} )");
    Dialog_Show(playerid, CreditosRippzypp, DIALOG_STYLE_MSGBOX, "{FFFFFF}Cr�ditos", Dialog, "Fechar", #);
    return 1;
}

CMD:identidade(playerid)
{
    new Identidade[900];
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Nome: {32CD32}%s\n", PegarNick(playerid));
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Level: {32CD32}%s\n", DinheiroSeparar(Jogador[playerid][Level]));
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Experi�ncia: {32CD32}%d\n", Jogador[playerid][Experiencia]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Profiss�o: {32CD32}%s\n", Jogador[playerid][Profissao]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Doen�a: {FA8072}%s\n", Doencas[Jogador[playerid][Doenca]][DoencaNome]); 
    // strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Dinheiro Sujo: {fc031c}$%s\n", DinheiroSeparar(Jogador[playerid][DinheiroSujo]));
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Sexo: %s\n", JogadorSexo(1, playerid));
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Skin: {32CD32}%d\n", Jogador[playerid][Skin]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Vacina: {32CD32}%s\n", SegundosParaMinutos(Jogador[playerid][Vacina])); 
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Vip: %s\n", IsVip(playerid) ? ("{32CD32}Sim") : ("{FF4500}N�o"));
    if(strcmp(Jogador[playerid][Casado], "*")) strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Casado(a): %s\n", Jogador[playerid][Casado]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Coins: {32CD32}%s\n", DinheiroSeparar(Jogador[playerid][Coins]));
    if(Jogador[playerid][pNumero] != 0) strcatEx(Identidade, "{1C1C1C}� {FFFFFF}N�mero: {32CD32}%s\n", NumeroSeparar(Jogador[playerid][pNumero]));
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Aviso(s): {FF0000}%d\n", Jogador[playerid][Avisos]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Registro(s): {00FF00}%s\n", ConverterSegundosEx(gettime()-Jogador[playerid][Registro]));
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Email: {00FF00}%s\n\n", Jogador[playerid][Email]);
    /*strcat(Identidade, "{FFFFFF}Diversos:\n");
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Adubos: {32CD32}%d\n", Jogador[playerid][Adubos]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}�guas: {32CD32}%d\n", Jogador[playerid][Agua]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Kit de Reparos: {32CD32}%d\n", Jogador[playerid][KitReparos]);
    strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Kit M�dico: {32CD32}%d\n", Jogador[playerid][KitMedico]);
    //strcatEx(Identidade, "{1C1C1C}� {FFFFFF}Caixas: {32CD32}%d", Jogador[playerid][PandoraCaixa]);*/
    Dialog_Show(playerid, IdentidadeRipzRC, DIALOG_STYLE_MSGBOX, "{FF0000}Sua Identidade", Identidade, "Fechar", #);
    return 1;
}

CMD:recompensas(playerid)
{
    new Enviar[128],
        Cache:Conectar;
    format(Enviar, sizeof(Enviar), "SELECT * FROM `recompensas` WHERE `Nome` = '%s'", PegarNick(playerid));
    Conectar = mysql_query(IDConexao, Enviar);
    if(mysql_errno(IDConexao) != 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | N�o foi poss�vel carregar suas recompensas!");
    new Contador = cache_num_rows();
    if(Contador < 1)
    {
        SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o possui recompensas!");
        cache_delete(Conectar);
        return 1;
    }

    new Dialog[900],
        NomeRecompensa[70],
        Recompensa[128],
        Data;
    strcat(Dialog, "Nome\tRecompensa\tData\n");
    for(new i=0; i < Contador; i++)
    {
        cache_get_value(i, "Nome", NomeRecompensa, 70);
        cache_get_value(i, "Recompensa", Recompensa, 128);
        cache_get_value_name_int(i, "Data", Data);
        strcatEx(Dialog, "{00FF00}%s\t%s\t{FF0000}%s\n", NomeRecompensa, Recompensa, GetDateFromTime(Data));
    }
    cache_delete(Conectar);
    Dialog_Show(playerid, RecompensaRippzyDia, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}Recompensas", Dialog, "Fechar", #);
    return 1;
}

CMD:profissao(playerid)
{
    if(IsMafia(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o, Use: /Anotacao");
    MostrarComandos(playerid);
    return 1;
}

CMD:anotacao(playerid)
{
    if(!IsMafia(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o, Use: /Profissao");
    MostrarComandos(playerid);
    return 1;
}

CMD:garagem(playerid)
{
    new Dialog[1500];
    strcat(Dialog, "Ve�culo\tPlaca\tEstado\n");  
    for(new i=0; i < MAX_SLOT_VEH; i++)
    {
        if(pVeiculo[playerid][i][MeuVeiculoModelo] > 0)
        {
            if(pVeiculo[playerid][i][VehConectado] == true) strcatEx(Dialog, "%d. {FFFFFF}Ve�culo: {FF0000}%s\t{FF4500}%s\t{00FF00}Conectado\n", i, GetVehicleNameByModel(pVeiculo[playerid][i][MeuVeiculoModelo]), pVeiculo[playerid][i][Placa]);
            else if(pVeiculo[playerid][i][Patio] > 0) strcatEx(Dialog, "%d. {FFFFFF}Ve�culo: {FF0000}%s\t{FF4500}%s\t{FFFF00}Apreendido\n", i, GetVehicleNameByModel(pVeiculo[playerid][i][MeuVeiculoModelo]), pVeiculo[playerid][i][Placa]);
            else if(pVeiculo[playerid][i][VehConectado] == false) strcatEx(Dialog, "%d. {FFFFFF}Ve�culo: {FF0000}%s\t{FF4500}%s\t{FF0000}Desconectado\n", i, GetVehicleNameByModel(pVeiculo[playerid][i][MeuVeiculoModelo]), pVeiculo[playerid][i][Placa]);    
        }
        else strcatEx(Dialog, "%d. {FFFFFF}Ve�culo: {FF0000}N/A\n", i);   
        if(i == 2){
            if(Jogador[playerid][Vip] < gettime()){
                break;
            }
        }
    }
    Dialog_Show(playerid, MenuVeiculo, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}Seus Ve�culos", Dialog, "Selecionar", "Fechar");
    return 1;
}

CMD:ajuda(playerid)
{
    new Dialog[400];
    strcat(Dialog, "{FFFFFF}Comandos\n");
    strcat(Dialog, "Casa\n");
    strcat(Dialog, "Empresa\n");
    strcat(Dialog, "Bases\n");
    strcat(Dialog, "Ve�culo\n");
    strcat(Dialog, "Utilit�rios\n");
    strcat(Dialog, "Arena/Modos\n");
    strcat(Dialog, "Vip e Nitro\n");
    strcat(Dialog, "Telefone P�blico\n");
    strcat(Dialog, "Ranks\n");
    strcat(Dialog, "Contato\n");
    strcat(Dialog, "Hobbies\n");
    Dialog_Show(playerid, AjudaMenu, DIALOG_STYLE_TABLIST, "{FF0000}Ajuda", Dialog, "Selecionar", "Fechar"); 
    return 1;
}

CMD:meulevel(playerid)
{
    new Dialog[200];
    strcatEx(Dialog, "{FFFFFF}Level: {00BFFF}%d\n", Jogador[playerid][Level]);
    strcatEx(Dialog, "{FFFFFF}Experi�ncia: {FF8C00}%d", Jogador[playerid][Experiencia]);
    Dialog_Show(playerid, SeuLevelInfo, DIALOG_STYLE_MSGBOX, "{FF0000}Seu Level", Dialog, "Fechar", "");
    return 1;
}

CMD:vantagensvip(playerid)
{
    new Dialog[1000];
    strcat(Dialog, "{FF0000}Comandos:\n");
    strcat(Dialog, "{f76d23}/Jetpack{FFFFFF} - Para pegar uma jetpack\n");
    strcat(Dialog, "{f76d23}/Pintar{FFFFFF} - Para alterar a cor de um ve�culo\n");
    strcat(Dialog, "{f76d23}/Virar{FFFFFF} - Para descapotar o ve�culo\n");
    strcat(Dialog, "{f76d23}/Continuar{FFFFFF} - Para retornar para sua �ltima posi��o\n");
    strcat(Dialog, "{f76d23}/Reparar{FFFFFF} - Para reparar seu ve�culo em qualquer lugar\n\n");
    strcat(Dialog, "{FFFF00}Geral:\n");
    strcat(Dialog, "{FFFFFF}1. N�o paga pelo test-drive e ganha {FFFF00}+2 minutos{FFFFFF} para testar\n");
    strcat(Dialog, "{FFFFFF}2. Nos modos de jogo voc� ganha {FFFF00}+3 armas{FFFFFF} diferente para combater o inimigo\n");
    strcat(Dialog, "{FFFFFF}3. {00BFFF}+7 Slots{FFFFFF} para ve�culos no {f76d23}/garagem\n");
    strcat(Dialog, "{FFFFFF}4. Cada UP com ser� com {00BFFF}5 de experi�ncia\n");
    strcat(Dialog, "{FFFFFF}Mais informa��es poder� ser encontrada no discord.");
    Dialog_Show(playerid, Vantagensvipmenue, DIALOG_STYLE_MSGBOX, "{FF0000}Vantagens VIP", Dialog, "Fechar", "");
    return 1;
}

CMD:vantagensnitro(playerid)
{
    new Dialog[1000];
    strcat(Dialog, "{FF0000}Comandos:\n");
    strcat(Dialog, "{f76d23}/Jetpack{FFFFFF} - Para pegar uma jetpack\n");
    strcat(Dialog, "{f76d23}/Virar{FFFFFF} - Para descapotar o ve�culo\n\n");
    strcat(Dialog, "{FFFF00}Geral:\n");
    strcat(Dialog, "{FFFFFF}1. Voc� tem acesso algumas �reas exclusivas do mapa\n");
    strcat(Dialog, "{FFFFFF}2. Voc� acesso para comprar acess�rios na loja de skins");
    Dialog_Show(playerid, Vantagensvipmenue, DIALOG_STYLE_MSGBOX, "{FF0000}Vantagens Nitro", Dialog, "Fechar", "");
    return 1;
}


CMD:mudarnick(playerid, params[])
{
    if(Jogador[playerid][Admin] < 5){
        if(Jogador[playerid][Coins] < 8000) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem 8.000 de coins");
    }

    new Dialog[300];
    strcat(Dialog, "{FFFFFF}Voc� est� alterando seu nick\n");
    strcatEx(Dialog, "Voc� tem {FFFF00}$%s{FFFFFF} de coins, depois que alterar ficar� com {FF0000}$%s\n\n", DinheiroSeparar(Jogador[playerid][Coins]), DinheiroSeparar(Jogador[playerid][Coins]-8000));
    strcat(Dialog, "{FFFF00}Coloque abaixo seu novo nick que deseja utilizar");
    Dialog_Show(playerid, RegistrarNovoNick, DIALOG_STYLE_INPUT, "{FF0000}Alterar Nick", Dialog, "Confirmar", "Cancelar");
    return 1;
}

CMD:mudarsenha(playerid, params[])
{
    Dialog_Show(playerid, RegistraNovaSenha, DIALOG_STYLE_INPUT, "{FF0000}Alterar Senha", "Coloque abaixo sua nova senha", "Confirmar", "Cancelar");
    return 1;
}

CMD:coresid(playerid)
{
    ShowVehColorListForPlayer(playerid);
    return 1;
}

CMD:verilegal(playerid)
{
    new Dialog[700];
    strcatEx(Dialog, "{FF6347}Drogas: {FFFFFF}%d\n", Jogador[playerid][Drogas]);
    strcatEx(Dialog, "{FF6347}Vasos: {FFFFFF}%d\n", Jogador[playerid][Vasos]);
    strcatEx(Dialog, "{FF6347}Sementes: {FFFFFF}%d\n", Jogador[playerid][Sementes]);
    strcatEx(Dialog, "{FF6347}LockPicks: {FFFFFF}%d\n", Jogador[playerid][LockPick]);
    strcatEx(Dialog, "{FF6347}C�psulas: {FFFFFF}%d\n", Jogador[playerid][Capsulas]);
    strcatEx(Dialog, "{FF6347}Pe�as: {FFFFFF}%d\n", Jogador[playerid][Pecas]);
    strcatEx(Dialog, "{FF6347}Dinamites: {FFFFFF}%d", Jogador[playerid][Dinamites]);
    Dialog_Show(playerid, FialozDSA1SD, DIALOG_STYLE_MSGBOX, "{FF0000}Ilegal", Dialog, "Fechar", "");
    return 1;
}

CMD:beco(playerid)
{
    if(strcmp(Jogador[playerid][Profissao], "Plantador de Maconha")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    EnviarGps(playerid, 2445.4421,-1970.0737,13.5469);
    SendClientMessage(playerid, -1, "| MAFIA | Foi marcado em seu mapa o beco");
    return 1;
}

CMD:hq(playerid)
{
    if(!strcmp(Jogador[playerid][Profissao], "Desempregado")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem profiss�o");
    for(new i=0; i < sizeof(pAgencia); i++)
    {
        if(strcmp(Jogador[playerid][Profissao], pAgencia[i][ProfissaoNome])) continue;
        EnviarGps(playerid, pAgencia[i][HQx], pAgencia[i][HQy], pAgencia[i][HQz]);
        SendClientMessage(playerid, -1, "| GPS | Foi marcado em seu mapa a sua HQ");
        break;
    }
    return 1;
}

CMD:gp(playerid, params[])
{
    if(Jogador[playerid][TagPersonalizada] != 6) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    new MsgAA[70];
    if(sscanf(params, "s[70]", MsgAA)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Gp [Mensagem]");

    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "| CHAT-GIRL | %s[%d] disse: %s", PegarNick(playerid), playerid, MsgAA);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(Jogador[i][TagPersonalizada] != 6 && Jogador[i][Admin] < 2) continue;
        SendClientMessage(i, 0xFF69B4FF, Mensagem);
    }

    return 1;
}

CMD:transferir(playerid, params[])
{
    if(Jogador[playerid][Level] < 10) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� s� pode transferir a partir do level 10");
    if(pTempo[playerid][TransferirMao] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� ainda n�o pode transferir, aguarde");
    new id, 
        vtrans
    ;
    if(sscanf(params, "dd", id, vtrans)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Transferir [ID] [Valor]");
    if(id == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode transferir para si mesmo");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o conectado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o conectado(a)");
    new Distancia = GetDistanceBetweenPlayers(playerid, id);
    if(Distancia > 5) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� muito longe!");
    if(vtrans > 5000 || vtrans < 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� pode transferir at� $5.000");
    if(Jogador[playerid][Dinheiro] < vtrans) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem toda essa quantia na m�o");
    if(Jogador[id][Level] < 5) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o transferir dinheiro para um(a) jogador(a) abaixo do level 5");

    // ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0, 1);
    // ApplyAnimation(id, "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0, 1);

    pTempo[playerid][TransferirMao] = gettime()+300;
    new Mensagem[128];
    format(Mensagem, sizeof(Mensagem), "| TRANSFER�NCIA | Voc� recebeu $%s do(a) jogador(a) %s[%d]", DinheiroSeparar(vtrans), PegarNick(playerid), playerid);
    SendClientMessage(id, 0xFFFF00FF, Mensagem);
    format(Mensagem, sizeof(Mensagem), "| TRANSFER�NCIA | Voc� enviou $%s para o(a) jogador(a) %s[%d]", DinheiroSeparar(vtrans), PegarNick(id), id);
    SendClientMessage(playerid, 0xFFFF00FF, Mensagem);
    Jogador[playerid][Dinheiro] -= vtrans;
    Jogador[id][Dinheiro] += vtrans;
    return 1;
}

stock MostrarRadio(playerid)
{
    new DialogRadio[528];
    strcat(DialogRadio, "R�dio\n");
    strcat(DialogRadio, "R�dio Hunter\n");
    strcat(DialogRadio, "R�dio 80s\n");
    strcat(DialogRadio, "R�dio 90s\n");
    strcat(DialogRadio, "R�dio Kpop\n");
    strcat(DialogRadio, "R�dio Brega-Funk\n");
    strcat(DialogRadio, "R�dio Funk JP\n");
    strcat(DialogRadio, "R�dio Sertanejo\n");
    strcat(DialogRadio, "R�dio Funk Perfect\n");
    strcat(DialogRadio, "R�dio DJ Alok\n");
    strcat(DialogRadio, "R�dio Funk de Quebrada\n");
    strcat(DialogRadio, "R�dio Trap\n");
    strcat(DialogRadio, "R�dio Sad\n");
    strcat(DialogRadio, "R�dio Hitz\n");
    strcat(DialogRadio, "R�dio Rippzy\n");
    strcat(DialogRadio, "+ {FF0000}Desligar r�dio\n");
    Dialog_Show(playerid, Radio, DIALOG_STYLE_TABLIST_HEADERS, "{FF0000}MP4", DialogRadio, "Selecionar", "Fechar");
    return 1;
}

CMD:t(playerid, params[])
{
    if(Jogador[playerid][Celular] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem celular");
    if(Jogador[playerid][Operadora] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem chip");
    if(GetPVarInt(playerid, "adasdasdasdasndma") == 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� est� com seu telegram bloqueado");

    new id, Mensagem[90];
    if(sscanf(params, "ds[90]", id, Mensagem)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /t [ID] [Mensagem]");
    if(id == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode enviar para s� mesmo");
    if(!IsPlayerConnected(id)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o conectado(a)");
    if(Jogador[id][Logado] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o logado(a)");
    if(Jogador[id][Celular] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o tem celular");
    if(Jogador[id][Operadora] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) n�o tem chip");
    if(Jogador[id][Preso] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Jogador(a) est� preso(a)");
    if(Jogador[id][Admin] > 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode mandar telegram para admin");
    if(GetPVarInt(id, "adasdasdasdasndma") == 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Est� com o telegram bloqueado");

    new Enviar[168];
    format(Enviar, sizeof(Enviar), "| TELEGRAM | Voc� enviou para %s[%d]: %s", PegarNick(id), id, Mensagem);
    SendClientMessage(playerid, 0x5d97f5FF, Enviar);

    format(Enviar, sizeof(Enviar), "| TELEGRAM | O(A) Jogador(a) %s[%d] enviou para voc�: %s", PegarNick(playerid), playerid, Mensagem);
    SendClientMessage(id, 0x5d97f5FF, Enviar);

    format(Enviar, sizeof(Enviar), "| TELEGRAM-ADMIN | O(A) Jogador(a) %s[%d] enviou para %s[%d]: %s", PegarNick(playerid), playerid, PegarNick(id), id, Mensagem);

    for(new i=0; i < MAX_PLAYERS; i++){
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(Jogador[i][Admin] < 1) continue;
        if(pAdmin[i][VerTelegram] == false) continue;
        SendClientMessage(i, 0x5d97f5FF, Enviar);
    }
    return 1;
}

CMD:bloqueartelegram(playerid)
{
    if(Jogador[playerid][Celular] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem celular");
    if(GetPVarInt(playerid, "adasdasdasdasndma") == 0){
        SetPVarInt(playerid, "adasdasdasdasndma", 1);
        SendClientMessage(playerid, 0x5d97f5FF, "| TELEGRAM | Voc� bloqueou seu telegram");
        return 1;
    }
    SetPVarInt(playerid, "adasdasdasdasndma", 0);
    SendClientMessage(playerid, 0x5d97f5FF, "| TELEGRAM | Voc� desbloqueou seu telegram");
    return 1;
}

CMD:continuar(playerid)
{
    //if(Jogador[playerid][Vip] < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    if(GetPVarInt(playerid, "TempoDoContinuar") == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode usar esse comando");
    if(GetPVarInt(playerid, "TempoDoContinuar") < gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode mais usar esse comando");
    SetPVarInt(playerid, "TempoDoContinuar", gettime()); 
    if(Jogador[playerid][uInterior] > 0) ForceSaida(playerid);
    else SetPlayerPos(playerid, Jogador[playerid][PosicaoX], Jogador[playerid][PosicaoY], Jogador[playerid][PosicaoZ]);
    SetPlayerFacingAngle(playerid,  Jogador[playerid][PosicaoA]);
    SendClientMessage(playerid, -1, "| CONTINUAR | Voc� voltou para sua �ltima posi��o do seu �ltimo login.");
    return 1;
}

CMD:usarlockpick(playerid)
{
    if(Jogador[playerid][LockPick] < 1) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem lockpick's");
    if(GetPVarInt(playerid, "LASDLASLDSALDASL") > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� precisa aguardar um pouco");

    new Float:Cbe[3],
        bool:alod;
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        for(new d=0; d < MAX_SLOT_VEH; d++)
        {
            if(pVeiculo[i][d][VehConectado] == false) continue;
            GetVehiclePos(pVeiculo[i][d][MeuVeiculoID], Cbe[0], Cbe[1], Cbe[2]);
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, Cbe[0], Cbe[1], Cbe[2])) continue;
            if(i == playerid) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode destrancar seu ve�culo");
            if(VeiculoServer[pVeiculo[i][d][MeuVeiculoID]][Tranca] == 0) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Esse ve�culo n�o est� trancado");
        
            SetPVarInt(playerid, "LASDLASLDSALDASL", gettime()+120);
            Jogador[playerid][LockPick]--;
            Jogador[playerid][Estrelas] += 3;

            new Mensagem[168];
            format(Mensagem, sizeof(Mensagem), "| CENTRAL | %s[%d] est� tentando destrancar um ve�culo em %s", PegarNick(playerid), playerid, GetPlayerZone(playerid));
            for(new p=0; p < MAX_PLAYERS; p++){
                if(!IsPlayerConnected(p)) continue;
                if(Jogador[p][Logado] == false) continue;
                if(!IsPolicia(p)) continue;
                if(pPolicia[p][PegouUniformePolicia] == false) continue;
                SendClientMessage(p, 0x1E90FFFF, Mensagem);
            }
            new rd = random(100);
            if(rd > 10) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Seu lockpick quebrou, tente novamente.");
            VeiculoServer[pVeiculo[i][d][MeuVeiculoID]][Tranca] = 0;
            SendClientMessage(playerid, 0xFFFF00FF, "| DESTRANCADO | Voc� destrancou o ve�culo.");
            alod = true;
            break;
        }
        if(alod == true) break;
    }
    if(alod == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o pode destrancar esse ve�culo");
    return 1;
}

CMD:utilitarios(playerid)
{
    new Dialog[400];
    strcatEx(Dialog, "{FFFFFF}Kit Reparos: {FFA500}%d\n", Jogador[playerid][KitReparos]);
    strcatEx(Dialog, "{FFFFFF}Kit M�dicos: {FFA500}%d\n", Jogador[playerid][KitMedico]);
    strcatEx(Dialog, "{FFFFFF}Lockpick: {FFA500}%d\n", Jogador[playerid][LockPick]);
    strcatEx(Dialog, "{FFFFFF}Cilindro: {FFA500}%d\n", Jogador[playerid][Cilindro]);
    strcatEx(Dialog, "{FFFFFF}�gua: {FFA500}%d", Jogador[playerid][Agua]);
    Dialog_Show(playerid, SemFuncao, DIALOG_STYLE_MSGBOX, "{FF0000}Informa��es", Dialog, "Fechar", #);
    return 1;
}