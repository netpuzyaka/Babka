#pragma once
#include <cstdint>


namespace CO {
	// dump.cs
	constexpr auto IsBeingHacked = 0x306E40; // public bool IsBeingHacked() { }
	constexpr auto IsFullyHacked = 0x4354D0; // public bool IsFullyHacked() { }
	constexpr auto IsHidden = 0x283A60; // public class StashContainer : StorageContainer || public bool IsHidden() { }
	constexpr auto Decrement = 0x18803D0; //public static float Decrement(float f) { }
	constexpr auto Increment = 0x18804D0; //public static float Increment(float f) { }
	constexpr auto Max = 0x1880820; //public static float Max(float f1, float f2, float f3) { }
	constexpr auto Clamp = 0x136BE10; //public static float Clamp(float value, float min, float max) { }
	constexpr auto MathfMin = 0x136c680;
	constexpr auto BaseNetworkable = 43631288;
	constexpr auto StartAttackCooldown = 0x2e9150;
	constexpr auto maxDistance = 0x278;
	constexpr auto DoFixedUpdate = 0x5f8340;
	constexpr auto RebuildAll = 0x86b8c0;
	constexpr auto HitTest = 43629816;
	constexpr auto ProcessAttack = 0x280e70;
}