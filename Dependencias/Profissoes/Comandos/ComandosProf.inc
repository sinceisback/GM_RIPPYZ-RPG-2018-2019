CMD:radio(playerid, params[])
{
    if(!IsPolicia(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o ao radio policial");
    if(pPolicia[playerid][PegouUniformePolicia] == false) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o est� fardado(a)!");
    if(Jogador[playerid][Mutado] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� foi mutado(a) pela administra��o, aguarde.");

    //if(!strcmp(Jogador[playerid][Profissao], "Desempregado")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    new Enviar[128];
    if(sscanf(params, "s[128]", Enviar)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Radio [Mensagem]");
    new Mensagem[200];
    format(Mensagem, sizeof(Mensagem), "| RADIO | %s[%d] diz: %s", PegarNick(playerid), playerid, Enviar);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(!IsPolicia(i)) continue;
        if(pPolicia[i][PegouUniformePolicia] == false) continue;
        if(GetPVarInt(i, "EventoJogador") > 0) continue;
        SendClientMessage(i, 0x4682B4FF, Mensagem);
    }
    return 1;
}

CMD:cp(playerid, params[])
{
    if(!strcmp(Jogador[playerid][Profissao], "Desempregado")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    if(IsMafia(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    if(Jogador[playerid][Mutado] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� foi mutado(a) pela administra��o, aguarde.");
    new Enviar[128];
    if(sscanf(params, "s[128]", Enviar)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Cp [Mensagem]");
    new Mensagem[200],
        id,
        zTagg[20];
    
	if(Jogador[playerid][BaseID] > 0) strcatEx(zTagg, "[%s]", Base[Jogador[playerid][BaseID]][BaseTag]);

    format(Mensagem, sizeof(Mensagem), "| CHAT-PROFISS�O | %s%s[%d] disse: %s", zTagg, PegarNick(playerid), playerid, Enviar);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(GetPVarInt(i, "EventoJogador") > 0) continue;
        if(GetPVarInt(i, "ChatProfissaoS") == 1) continue;
        if(strcmp(Jogador[playerid][Profissao], Jogador[i][Profissao])){
            if(strcmp(Jogador[playerid][Profissao], pAdmin[i][EspiandoProf]) || isnull(pAdmin[i][EspiandoProf])) continue;
        }
        
        for(new o=0; o < sizeof(pAgencia); o++){
            if(strcmp(Jogador[playerid][Profissao], pAgencia[o][ProfissaoNome])) continue;
            id = o;
            break;
        }
        SendClientMessage(i, pAgencia[id][CorProfissao], Mensagem);
    }
    return 1;
}

CMD:cm(playerid, params[])
{
    if(!strcmp(Jogador[playerid][Profissao], "Desempregado")) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    if(!IsMafia(playerid)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� n�o tem permiss�o");
    if(Jogador[playerid][Mutado] > gettime()) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Voc� foi mutado(a) pela administra��o, aguarde.");
    new Enviar[128];
    if(sscanf(params, "s[128]", Enviar)) return SendClientMessage(playerid, 0xFF4500FF, "| ERRO | Use: /Cm [Mensagem]");
    new Mensagem[200],
        id,
        zTagg[20];
    
	if(Jogador[playerid][BaseID] > 0) strcatEx(zTagg, "[%s]", Base[Jogador[playerid][BaseID]][BaseTag]);

    format(Mensagem, sizeof(Mensagem), "| CHAT-MAFIA | %s%s[%d] disse: %s", zTagg, PegarNick(playerid), playerid, Enviar);
    for(new i=0; i < MAX_PLAYERS; i++)
    {
        if(!IsPlayerConnected(i)) continue;
        if(Jogador[i][Logado] == false) continue;
        if(GetPVarInt(i, "EventoJogador") > 0) continue;
        if(GetPVarInt(i, "ChatProfissaoS") == 1) continue;
        if(strcmp(Jogador[playerid][Profissao], Jogador[i][Profissao])){
            if(strcmp(Jogador[playerid][Profissao], pAdmin[i][EspiandoProf]) || isnull(pAdmin[i][EspiandoProf])) continue;
        }

        for(new o=0; o < sizeof(pAgencia); o++){
            if(strcmp(Jogador[playerid][Profissao], pAgencia[o][ProfissaoNome])) continue;
            id = o;
            break;
        }
        SendClientMessage(i, pAgencia[id][CorProfissao], Mensagem);
    }
    return 1;
}

stock MostrarComandos(playerid)
{
    new Mensagem[1500];
    strcmp(Mensagem, "Comando - Informa��es\n");

    //Honestas
    if(!strcmp(Jogador[playerid][Profissao], "Gari"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/IniciarDupla{FFFFFF} - Para ativar o modo dupla\n\n\n");
        strcat(Mensagem, "{FF0000}Modo Dupla:{FFFFFF}\n");
        strcat(Mensagem, "{FF4500}1. Como usar o modo dupla: {FFFF00}Quando o seu parceiro(a) estiver no carona use /IniciarDupla\n");
        strcat(Mensagem, "{FF4500}2. Caso n�o queria trabalhar em dupla, basta pegar o primeiro lixo que voc� iniciar� sozinho(a)\n");
        strcat(Mensagem, "{FF4500}3. Depois de coletar o lixo, vai aparecer em seu minimapa o simbolo do caminh�o para descarregar");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Transportador de Carne"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Acougue{FFFFFF} - Para marcar em seu mapa onde pega as caixas com carne");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Uber Eats"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Entregas{FFFFFF} - Para iniciar entregas");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Uber"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Aceitar [ID]{FFFFFF} - Para aceitar uma corrida\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Policial Militar"))
    {
        strcat(Mensagem, "{4682B4}/Algemar [ID]{FFFFFF} - Para algemar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Desalgemar [ID]{FFFFFF} - Para desalgemar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Abordar [ID]{FFFFFF} - Para abordar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Prender [ID]{FFFFFF} - Para prender um jogador\n");
        strcat(Mensagem, "{4682B4}/Radio [Mensagem]{FFFFFF} - Para enviar mensagem todos os policias\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Localizar [ID]{FFFFFF} - Para localizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Deslocalizar{FFFFFF} - Para deslocalizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Multas{FFFFFF} - Para visualizar as multas\n");
        strcat(Mensagem, "{4682B4}/Multar [ID] [Valor] [Multa]{FFFFFF} - Para multar um jogador\n");
        strcat(Mensagem, "{4682B4}/PrenderArmas [ID]{FFFFFF} - Para prender armas de um jogador\n");
        strcat(Mensagem, "{4682B4}/Procurados{FFFFFF} - Para visualizar procurados(as)\n");
        strcat(Mensagem, "{4682B4}/ArrombarPorta{FFFFFF} - Para arrombar uma porta de casa\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Corregedoria"))
    {
        strcat(Mensagem, "{4682B4}/Localizar [ID]{FFFFFF} - Para localizar um(a) policial\n");
        strcat(Mensagem, "{4682B4}/Deslocalizar{FFFFFF} - Para deslocalizar um(a) policial\n");
        strcat(Mensagem, "{4682B4}/PrenderPolicia [ID] [Tempo] [Motivo]{FFFFFF} - Para prender um(a) policial que esteja cometendo uma infra��o\n");
        strcat(Mensagem, "{4682B4}/MotivoPrisoes{FFFFFF} - Para ver motivos e tempo de pris�es\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Motorista de �nibus"))
    {
        strcat(Mensagem, "{4682B4}/Rotas{FFFFFF} - Para iniciar uma rota\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Plantador de Maconha"))
    {
        strcat(Mensagem, "{FF6347}/VerIlegal{FFFFFF} - Para ver oque voc� tem de ilegal\n");
        strcat(Mensagem, "{FF6347}/Beco{FFFFFF} - Para localizar o local de compra\n");
        strcat(Mensagem, "{FF6347}/Boca{FFFFFF} - Para localizar a boca de tr�fico\n");
        strcat(Mensagem, "{FF6347}/Traficante{FFFFFF} - Para localizar um traficante\n");
        strcat(Mensagem, "{FF6347}/Plantar{FFFFFF} - Para plantar uma semente\n");
        strcat(Mensagem, "{FF6347}/Colher{FFFFFF} - Para colher uma muda\n");
        strcat(Mensagem, "{FF6347}/Adubo{FFFFFF} - Para dar boost no plantio use o adubo\n");
        strcat(Mensagem, "{FF6347}/Hq{FFFFFF} - Para marcar HQ do seu cargo\n");
        strcat(Mensagem, "{FF6347}/Cm{FFFFFF} - Para enviar mensagem para seu outros(as) do seu cargo\n");
        strcat(Mensagem, "{FF6347}/Regar{FFFFFF} - Para molhar sua muda caso ela precise ( Voc� precisa de �gua )\n\n");
        strcat(Mensagem, "{FF0000}Observa��es:{FFFFFF}\n");
        strcat(Mensagem, "{FF4500}1. O Adubo n�o � obrig�torio comprar\n");
        strcat(Mensagem, "{FF4500}2. Voc� precisa sempre ter �gua com voc� para regar sua muda ou ela irar morrer\n");
        strcat(Mensagem, "{FF4500}3. {FFFF00}�gua voc� compra em uma loja de utilit�rios e adubos, sementes etc. no beco\n");
        strcat(Mensagem, "{FF4500}4. Voc� pode visualizar suas �guas e adubos pelo /identidade");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Transportador"))
    {
        strcat(Mensagem, "{4682B4}/Encomendas{FFFFFF} - Para iniciar entregas ( Com ou sem parceiro(a) )\n");
        strcat(Mensagem, "{4682B4}/Dupla{FFFFFF} - Para iniciar ou encerrar uma entrega com amigo(a)\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o\n\n");
        strcat(Mensagem, "{FF0000}Observa��o:\n");
        strcat(Mensagem, "{FF4500}Caso queira trabalhar em dupla, digite /Dupla antes de /Encomendas");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Lenhador"))
    {
        strcat(Mensagem, "{4682B4}/Derrubar{FFFFFF} - Para derrubar uma �rvore\n");
        strcat(Mensagem, "{4682B4}/Lixar{FFFFFF} - Para lixar uma madeira\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Advogado"))
    {
        strcat(Mensagem, "{4682B4}/SoltarPreso [ID]{FFFFFF} - Para soltar um(a) determinado(a) preso(a)\n");
        strcat(Mensagem, "{4682B4}/Presos{FFFFFF} - Para visualizar lista de presos(as)\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Ladr�o de Ve�culos"))
    {
        strcat(Mensagem, "{FF6347}/Cm{FFFFFF} - Para enviar mensagem para seu outros(as) do seu cargo\n");
        strcat(Mensagem, "{FF0000}Objetivo:\n");
        strcat(Mensagem, "{FF4500}Procure por garagens espalhada pelo mapa e roube o ve�culo l�");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Param�dico"))
    {
        strcat(Mensagem, "{4682B4}/Reviver{FFFFFF} - Para reviver um(a) morto(a)\n");
        strcat(Mensagem, "{4682B4}/Feridos{FFFFFF} - Para visualizar jogadores que precisam de curativos\n");
        strcat(Mensagem, "{4682B4}/Curativo [ID] [Valor]{FFFFFF} - Para enviar uma proposta de curativos\n");
        strcat(Mensagem, "{4682B4}/FazerCurativos{FFFFFF} - Para efetuar os curativos\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o\n\n");
        strcat(Mensagem, "{FF0000}Objetivo:\n");
        strcat(Mensagem, "{FF4500}Quando um(a) jogador(a) estiver morto(a) o mesmo vai aparecer no mapa com �cone de cora��o\n");
        strcat(Mensagem, "{FF4500}Basta voc� ir at� o local e reviver o(a) mesmo(a)\n\n");
        strcat(Mensagem, "{FF0000}Farda:\n");
        strcat(Mensagem, "{FF4500}Para pegar sua farda entre no dentro do hospital e v� at� uma sala nos fundos\n");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Ourives"))
    {
        strcat(Mensagem, "{4682B4}/Cavar{FFFFFF} - Para cavar e procurar uma pedra\n");
        strcat(Mensagem, "{4682B4}/LocalCavar{FFFFFF} - Para marcar o local apropriado para cavar\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o\n\n");
        strcat(Mensagem, "{FF0000}Objetivo:\n");
        strcat(Mensagem, "{FF4500}Voc� precisa ir at� um determinado local e cavar em volta do lago");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Bombeiro"))
    {
        strcat(Mensagem, "{4682B4}/Fogo{FFFFFF} - Para iniciar um trabalho\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Motorista de Carro Forte"))
    {
        strcat(Mensagem, "{4682B4}/Carregar{FFFFFF} - Para iniciar um reabastecimento do seu carro forte\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Assassino"))
    {
        strcat(Mensagem, "{FF6347}/VerIlegal{FFFFFF} - Para ver oque voc� tem de ilegal\n");
        strcat(Mensagem, "{FF6347}/Contratados{FFFFFF} - Para ver oque os(as) jogadores(as) em contrato\n");
        strcat(Mensagem, "{FF6347}/Boca{FFFFFF} - Para localizar a boca de tr�fico\n");
        strcat(Mensagem, "{FF6347}/Traficante{FFFFFF} - Para localizar um traficante\n");
        strcat(Mensagem, "{FF6347}/Hq{FFFFFF} - Para marcar HQ do seu cargo\n");
        strcat(Mensagem, "{FF6347}/Cm{FFFFFF} - Para enviar mensagem para seu outros(as) do seu cargo");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Produtor da M�fia"))
    {
        strcat(Mensagem, "{FF6347}/VerIlegal{FFFFFF} - Para ver oque voc� tem de ilegal\n");
        strcat(Mensagem, "{FF6347}/Boca{FFFFFF} - Para localizar a boca de tr�fico\n");
        strcat(Mensagem, "{FF6347}/Traficante{FFFFFF} - Para localizar um traficante\n");
        strcat(Mensagem, "{FF6347}/Hq{FFFFFF} - Para marcar HQ do seu cargo\n");
        strcat(Mensagem, "{FF6347}/Cm{FFFFFF} - Para enviar mensagem para seu outros(as) do seu cargo\n\n");
        strcat(Mensagem, "1. Voc� precisa localizar um traficante e comprar as c�psulas ou as pe�as de armas\n");
        strcat(Mensagem, "2. Ap�s isso retorne para HQ e produza as armas ou muni��es e entregue");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Assaltante"))
    {
        strcat(Mensagem, "{FF6347}/VerIlegal{FFFFFF} - Para ver oque voc� tem de ilegal\n");
        strcat(Mensagem, "{FF6347}/Assaltar [ID]{FFFFFF} - Para assaltar um(a) jogador(a)\n");
        strcat(Mensagem, "{FF6347}/AssaltarCarroForte [ID]{FFFFFF} - Para assaltar um Carro Forte\n");
        strcat(Mensagem, "{FF6347}/AssaltarCaixa{FFFFFF} - Para assaltar um Caixa Eletr�nico\n");
        strcat(Mensagem, "{FF6347}/RoubarLoja{FFFFFF} - Para assaltar uma lojinha\n");
        strcat(Mensagem, "{FF6347}/Boca{FFFFFF} - Para localizar a boca de tr�fico\n");
        strcat(Mensagem, "{FF6347}/Traficante{FFFFFF} - Para localizar um traficante\n");
        strcat(Mensagem, "{FF6347}/Hq{FFFFFF} - Para marcar HQ do seu cargo\n");
        strcat(Mensagem, "{FF6347}/Cm{FFFFFF} - Para enviar mensagem para seu outros(as) do seu cargo");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Petroleiro"))
    {
        strcat(Mensagem, "{4682B4}/AbastecerPosto{FFFFFF} - Para abastecer o posto de gasolina\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Meteorologista"))
    {
        strcat(Mensagem, "{4682B4}/AtivarSatelite{FFFFFF} - Para ativar o sat�lite\n");
        strcat(Mensagem, "{4682B4}/CarregarDados{FFFFFF} - Para carregar os dados do sat�lite\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Maquinista"))
    {
        strcat(Mensagem, "{4682B4}/Estacao{FFFFFF} - Para embarcar passageiros(as)\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Piloto"))
    {
        strcat(Mensagem, "{4682B4}/Aeros{FFFFFF} - Para carregar o avi�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/EscadaAviao{FFFFFF} - Para colocar/tirar a escada do AT-400\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para falar no chat profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Ex�rcito"))
    {
        strcat(Mensagem, "{4682B4}/Algemar [ID]{FFFFFF} - Para algemar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Desalgemar [ID]{FFFFFF} - Para desalgemar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Abordar [ID]{FFFFFF} - Para abordar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Acompanhamento [ID]{FFFFFF} - Para iniciar um acompanhamento\n");
        strcat(Mensagem, "{4682B4}/Prender [ID]{FFFFFF} - Para prender um jogador\n");
        strcat(Mensagem, "{4682B4}/Radio [Mensagem]{FFFFFF} - Para enviar mensagem todos os policias\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Localizar [ID]{FFFFFF} - Para localizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Deslocalizar{FFFFFF} - Para deslocalizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Procurados{FFFFFF} - Para visualizar procurados(as)\n");
        strcat(Mensagem, "{4682B4}/PrenderArmas [ID]{FFFFFF} - Para prender armas de um jogador\n");
        strcat(Mensagem, "{4682B4}/Multas{FFFFFF} - Para visualizar as multas\n");
        strcat(Mensagem, "{4682B4}/Multar [ID] [Valor] [Multa]{FFFFFF} - Para multar um jogador\n");
        strcat(Mensagem, "{4682B4}/Procurar [ID] [Motivo]{FFFFFF} - Para colocar um jogador na lista de procurados\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");   
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Aeron�utica"))
    {
        strcat(Mensagem, "{4682B4}/Algemar [ID]{FFFFFF} - Para algemar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Desalgemar [ID]{FFFFFF} - Para desalgemar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Abordar [ID]{FFFFFF} - Para abordar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Acompanhamento [ID]{FFFFFF} - Para iniciar um acompanhamento\n");
        strcat(Mensagem, "{4682B4}/Prender [ID]{FFFFFF} - Para prender um jogador\n");
        strcat(Mensagem, "{4682B4}/Radio [Mensagem]{FFFFFF} - Para enviar mensagem todos os policias\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Localizar [ID]{FFFFFF} - Para localizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Deslocalizar{FFFFFF} - Para deslocalizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Procurados{FFFFFF} - Para visualizar procurados(as)\n");
        strcat(Mensagem, "{4682B4}/PrenderArmas [ID]{FFFFFF} - Para prender armas de um jogador\n");
        strcat(Mensagem, "{4682B4}/Multas{FFFFFF} - Para visualizar as multas\n");
        strcat(Mensagem, "{4682B4}/Multar [ID] [Valor] [Multa]{FFFFFF} - Para multar um jogador\n");
        strcat(Mensagem, "{4682B4}/Procurar [ID] [Motivo]{FFFFFF} - Para colocar um jogador na lista de procurados\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");   
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Marinha"))
    {
        strcat(Mensagem, "{4682B4}/Algemar [ID]{FFFFFF} - Para algemar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Desalgemar [ID]{FFFFFF} - Para desalgemar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Abordar [ID]{FFFFFF} - Para abordar um jogador procurado\n");
        strcat(Mensagem, "{4682B4}/Acompanhamento [ID]{FFFFFF} - Para iniciar um acompanhamento\n");
        strcat(Mensagem, "{4682B4}/Prender [ID]{FFFFFF} - Para prender um jogador\n");
        strcat(Mensagem, "{4682B4}/Radio [Mensagem]{FFFFFF} - Para enviar mensagem todos os policias\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Localizar [ID]{FFFFFF} - Para localizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Deslocalizar{FFFFFF} - Para deslocalizar um procurado(a)\n");
        strcat(Mensagem, "{4682B4}/Procurados{FFFFFF} - Para visualizar procurados(as)\n");
        strcat(Mensagem, "{4682B4}/PrenderArmas [ID]{FFFFFF} - Para prender armas de um jogador\n");
        strcat(Mensagem, "{4682B4}/Multas{FFFFFF} - Para visualizar as multas\n");
        strcat(Mensagem, "{4682B4}/Multar [ID] [Valor] [Multa]{FFFFFF} - Para multar um jogador\n");
        strcat(Mensagem, "{4682B4}/Procurar [ID] [Motivo]{FFFFFF} - Para colocar um jogador na lista de procurados\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");   
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Mec�nico"))
    {
        strcat(Mensagem, "{4682B4}/MecanicoAceitar [ID] [Pre�o]{FFFFFF} - Para aceitar um chamado\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "A�ougueiro"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/CortarCarne{FFFFFF} - Para cortar carne");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Per�cia"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Pericia{FFFFFF} - Para iniciar um servi�o\n");
        strcat(Mensagem, "{4682B4}/AnalisarCorpo{FFFFFF} - Para analisar um corpo");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Eletricista"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Poste{FFFFFF} - Para iniciar um servi�o\n");
        strcat(Mensagem, "{4682B4}/ArrumarPoste{FFFFFF} - Para arrumar o poste\n");
        strcat(Mensagem, "{4682B4}/Escada{FFFFFF} - Para colocar uma escada\n");
        strcat(Mensagem, "{4682B4}/MoverEscada{FFFFFF} - Para mover a escada\n");
        strcat(Mensagem, "{4682B4}/RemoverEscada{FFFFFF} - Para remover a escada");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Leiteiro"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/TirarLeite{FFFFFF} - Para retirar o leite da vaca");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Mergulhador"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Mar{FFFFFF} - Para iniciar o servi�o\n");
        strcat(Mensagem, "{4682B4}/UsarCilindro{FFFFFF} - Para usar o cilindro de oxig�nio");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Vendedor de Rua"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o\n");
        strcat(Mensagem, "{4682B4}/Estacionar{FFFFFF} - Para estacionar seu ve�culo e iniciar as vendas");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Terrorista"))
    {
        strcat(Mensagem, "{FF6347}/VerIlegal{FFFFFF} - Para ver oque voc� tem de ilegal\n");
        strcat(Mensagem, "{FF6347}/Hq{FFFFFF} - Para marcar HQ do seu cargo\n");
        strcat(Mensagem, "{FF6347}/Cm{FFFFFF} - Para enviar mensagem para seu outros(as) do seu cargo\n");
        strcat(Mensagem, "{FF6347}/ArmarBomba{FFFFFF} - Para colocar uma bomba no local\n");
        strcat(Mensagem, "{FF6347}/HomemBomba{FFFFFF} - Para se explodir");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Pizza Delivery"))
    {
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Transportador de Concreto"))
    {
        strcat(Mensagem, "{4682B4}/Concreto{FFFFFF} - Para iniciar uma entrega\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Transportador de Eletr�nicos"))
    {
        strcat(Mensagem, "{4682B4}/CarregarEletronico{FFFFFF} - Para iniciar uma entrega\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o");
    }

    else if(!strcmp(Jogador[playerid][Profissao], "Fazendeiro"))
    {
        strcat(Mensagem, "{4682B4}/PlantarSemente{FFFFFF} - Para plantar uma semente\n");
        strcat(Mensagem, "{4682B4}/Feno{FFFFFF} - Para localizar o local de entrega\n");
        strcat(Mensagem, "{4682B4}/Cp [Mensagem]{FFFFFF} - Para enviar mensagem no chat profiss�o\n");
        strcat(Mensagem, "{4682B4}/Hq{FFFFFF} - Para marcar HQ da sua profiss�o");
    }
    Dialog_Show(playerid, ListaComandoProfissao, DIALOG_STYLE_MSGBOX, Jogador[playerid][Profissao], Mensagem, "Fechar", "");
    return 1;
}