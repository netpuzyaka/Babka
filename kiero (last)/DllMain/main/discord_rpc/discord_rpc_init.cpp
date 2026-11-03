#include "discord_rpc_init.h"
#include <ctime>
#include "../auth/sk.h"



void Discord::Initialize()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize("1234511065153273947", &Handle, 1, NULL);
}

void Discord::Update()
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    static auto elapsed = std::time(nullptr);

    discordPresence.details = skCrypt("Playing Rust");
    discordPresence.state = "Plays with the best cheat";
    discordPresence.largeImageKey = "https://media1.tenor.com/m/3YoNXk81-BMAAAAC/z-%D1%81%D0%B2%D0%BE.gif";
    discordPresence.startTimestamp = elapsed;
    discordPresence.smallImageKey = "rust_ico";
    discordPresence.button1_label = "Discord";
    discordPresence.button1_url = "https://discord.gg/mPp3qzNXXA";
    discordPresence.button2_label = "Youtube";
    discordPresence.button2_url = "https://www.youtube.com/channel/UCrc6SBNtiTHz08PFltbFfhA";
    Discord_UpdatePresence(&discordPresence);
}


void Discord::Shutdown()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Shutdown();
}
