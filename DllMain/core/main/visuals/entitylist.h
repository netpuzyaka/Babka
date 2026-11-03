#include "player.h"
#include "world.h"
void entitylist() {
	off_arrows_alpha = ImLerp(off_arrows_alpha, off_arrows_animation ? 1.f : 0.f, ImGui::GetIO().DeltaTime * 4);
	if (off_arrows_alpha <= 0.1f || off_arrows_alpha >= 0.99f) off_arrows_animation = !off_arrows_animation;
	il2cpp::main_camera = il2cpp::get_main_camera();
	auto entityList = BaseNetworkable::clientEntities()->entityList();
	for (int i = 0; i < entityList->vals->size; i++) {
		uintptr_t Entity = *reinterpret_cast<uintptr_t*>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
		if (!Entity) continue;
		uintptr_t Object = *reinterpret_cast<uint64_t*>(Entity + 0x10);
		if (!Object) continue;
		uintptr_t ObjectClass = *reinterpret_cast<uint64_t*>(Object + 0x30);
		if (!ObjectClass) continue;

		pUncStr name = *reinterpret_cast<pUncStr*>(ObjectClass + 0x60); if (!name) continue;
		char* buff = name->stub;

		if (!reinterpret_cast<BaseEntity*>(Entity)->IsValid()) { continue; }
		if (!reinterpret_cast<Component*>(Entity)->gameObject()) { continue; }
		if (strstr(buff, ("Local"))) { continue; }

		if (reinterpret_cast<BaseCombatEntity*>(Entity)->IsPlayer()) {
			BasePlayer* Player = (BasePlayer*)Entity;
			if (!Player->is_alive()) continue;
			if (!Player->IsNpc()) {
				player_esp(Player);
			}
		}
		else {
			world_esp((BaseEntity*)Entity,buff);
		}
	}
}