#include <YSI_Coding\y_hooks>

enum
{
    MensagemServidor[158]
};

new ReiniciarTempo,
    bool:Reiniciar,
    bool:BloquearFunc,
    bool:HorarioCerto;

new MensagemSV[][MensagemServidor] =
{
    {"[ {FF0000}!{FFFFFF} ] Voc� pode tirar suas d�vidas usando o comando {FFA500}/duvida"},
    {"[ {FF0000}!{FFFFFF} ] Encontrou um bug? reporte-o para n�s e ganhe recompensas!"},
    // {"[ {FF0000}!{FFFFFF} ] Use {FFA500}/Atendimento{FFFFFF} para solicitar um atendimento de um admin"},
    // {"[ {FF0000}!{FFFFFF} ] Para solicitar um atendimento use {FFA500}/Atendimento"},
    {"[ {FF0000}!{FFFFFF} ] Voc� ainda n�o est� em nosso discord? {FFA500}discord.gg/knNHxTy"},
    {"[ {FF0000}!{FFFFFF} ] Nosso canal no youtube: {FFA500}youtube.com/rippzycity"},
    // {"[ {FF0000}!{FFFFFF} ] Nosso canal no youtube: {FFA500}youtube.com/rippzy"},
    {"[ {FF0000}!{FFFFFF} ] Encontrou um cheater ou jogador quebrando as regras? Reporte-o usando {FFA500}/relatorio"},
    // {"[ {FF0000}!{FFFFFF} ] N�o perca sua habilita��o, v� at� o detran para regulariz�-la"},
    // {"[ {FF0000}!{FFFFFF} ] N�o estacione na cal�ada, seu ve�culo poder� ser guinchado"},
    {"[ {FF0000}!{FFFFFF} ] Voc� pode obter vantagens no servidor adquirindo o {FFA500}VIP{FFFFFF} ou dando {FFA500}Boost{FFFFFF} em nosso discord"},
    {"[ {FF0000}!{FFFFFF} ] Ainda n�o vinculou sua conta do servidor com o discord? Use {FFA500}/Discord"},
    {"[ {FF0000}!{FFFFFF} ] Voc� pode tirar suas d�vidas sobre o servidor utilizando o comando {FFA500}/Ajuda"},
    {"[ {FF0000}!{FFFFFF} ] Servidor sem admin? est� querendo reportar um jogador? Use {FFA500}/Reportar"},

    // Parceiros
    {"[ {FF0000}!{FFFFFF} ] Parceiro Oficial [Rocow]: {FFA500}twitch.tv/rocow_"},
    {"[ {FF0000}!{FFFFFF} ] Parceiro Oficial [PC_Fraco]: {FFA500}youtube.com/pcfracobr"},
    {"[ {FF0000}!{FFFFFF} ] Parceiro Oficial [Ansu]: {FFA500}youtube.com/mrjovesson"},
    {"[ {FF0000}!{FFFFFF} ] Parceiro Oficial [Noguiin]: {FFA500}youtube.com/noginbr"},
    {"[ {FF0000}!{FFFFFF} ] Parceiro Oficial [Luc�o]: {FFA500}youtube.com/RadioNaVibe"},

    {"[ {FF0000}!{FFFFFF} ] Voc� pode visualizar as atualiza��es em nosso f�rum ou discord"},
    // {"[ {FF0000}!{FFFFFF} ] Voc� pode trocar de voips apenas dando um comando {FFA500}/Voips"},
    {"[ {FF0000}!{FFFFFF} ] Saiba as vantagens do VIP utilizando o comando {FFA500}/VantagensVIP"},
    {"[ {FF0000}!{FFFFFF} ] Saiba as vantagens do Nitro Booster utilizando o comando {FFA500}/VantagensNitro"},
    // {"[ {FF0000}!{FFFFFF} ] Solicite o servi�o de mec�nico acessando seu celular {FFA500}/Celular"},
    {"[ {FF0000}!{FFFFFF} ] Est� sem ve�culo? abra seu celular e solicite um uber {FFA500}/Celular"},
    {"[ {FF0000}!{FFFFFF} ] Voc� tem coins e precisa de VIP? Utilize o comando {FFA500}/Loja{FFFFFF} e fa�a sua compra"},
    {"[ {FF0000}!{FFFFFF} ] Voc� sabia que dando boost em nosso discord voc� ganha vantagens aqui no servidor?"},
    {"[ {FF0000}!{FFFFFF} ] Voc� pode visualizar as atualiza��es em nosso f�rum ou discord"}
};

hook OnGameModeInit()
{
    SetTimer("MensagemAutomaticaServidor", 600000, true);
    SetTimer("ServidorReiniciar", 1000, true);
    return 1;
}

function EnviarReiniciar()
{
    SendRconCommand("gmx");
    return 1;
}

function MensagemAutomaticaServidor() return SendClientMessageToAll(-1, MensagemSV[random(sizeof(MensagemSV))][MensagemServidor]);
function ServidorReiniciar()
{
    ReiniciandoServidor();
    if(Reiniciar == false) return 1;
    if(HorarioCerto == false) return 1;
    if(BloquearFunc == true) return 1;
    BloquearFunc = true;

    SendRconCommand("password dasdass12adasda312sda");
    SendRconCommand("hostname Rippzy City RPG � | Reiniciando, aguarde.");
    for(new i=0; i < MAX_PLAYERS; i++){
        if(!IsPlayerConnected(i)) continue;
        Kick(i);
    }

    ReiniciarCasa(true); // Adicionar dependencias nas casas
    ReiniciarFabrica(true); // Adicionar dependencias nas fabricas
    ReiniciarEmpresa(true); // Adicionar dependencias nas empresas
    ReiniciarConcessionaria(true);
    ReiniciarBase(); // Adicionar dependencias nas bases

    SetTimer("EnviarReiniciar", 120000, false);
    return 1;
}

stock ReiniciandoServidor()
{
    new rHoras, rMinutos;
    gettime(rHoras, rMinutos);
    if(rHoras == 4 && rMinutos >= 50)
    {
        if(Reiniciar == false)
        {
            AlertaAdminStt = true;
            MostrarAdminAlerta();
            Reiniciar = true;   
            ReiniciarTempo = 600;
        }

        ReiniciarTempo--;
        new Mensagem[128];
        format(Mensagem, sizeof(Mensagem), "Reiniciando em ~r~%s", ConverterSegundosEx(ReiniciarTempo));
        TextDrawSetString(AlertaAdmin[2], ConverterTexto(Mensagem)); 
    }
    else if(rHoras == 5 && rMinutos == 0)
    {
        HorarioCerto = true;
    }
    return 1;
}