float w_last_syringe = 0.f;
BasePlayer* MatrixUpdater;
void TestFlying() {
	
	if (!LocalPlayer::Entity()->OnLadder()) {
		flyhackPauseTime = Mathf::Max(0.f, flyhackPauseTime - Time::deltaTime());
		bool inAir = false;
		float radius = LocalPlayer::Entity()->GetRadius();
		float height = LocalPlayer::Entity()->GetHeight(false);
		Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->position() + LocalPlayer::Entity()->playerModel()->position()) * 0.5f;
		Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
		Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
		float radius2 = radius - 0.05f;
		bool a = Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, QueryTriggerInteraction::Ignore);
		inAir = !a;

		if (inAir) {
			bool flag = false;

			Vector3 vector4 = (LocalPlayer::Entity()->playerModel()->position() - LocalPlayer::Entity()->lastSentTick()->position());
			float num3 = Mathf::Abs(vector4.y);
			float num4 = Misc::Magnitude2D(vector4);
			if (vector4.y >= 0.f) {
				flyhackDistanceVertical += vector4.y;
				flag = true;
			}
			if (num3 < num4) {
				flyhackDistanceHorizontal += num4;
				flag = true;
			}
			if (flag) {
				float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
				if (flyhackDistanceVertical > num6) {
				}
				float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
				float num8 = 5.f + num7;
				if (flyhackDistanceHorizontal > num8) {
				}
			}
		}
		else {
			flyhackDistanceHorizontal = 0.f;
			flyhackDistanceVertical = 0.f;
		}
		float flyhack_forgiveness_interia = 10.0f;
		float flyhack_forgiveness = 1.5f;
		float flyhack_extrusion = 1.85f;
		float num5 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num6 = ((LocalPlayer::Entity()->GetJumpHeight() + num5) * 3);

		VMaxFlyhack = num6;
		if (flyhackDistanceVertical <= (num6)) {
			VFlyhack = flyhackDistanceVertical;
		}
		if (VFlyhack >= VMaxFlyhack)
			VFlyhack = VMaxFlyhack;
		float num7 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num8 = ((5.f + num7) * 3);

		HMaxFlyhack = num8;
		if (flyhackDistanceHorizontal <= (num8)) {
			HFlyhack = flyhackDistanceHorizontal;
		}
		if (HFlyhack >= HMaxFlyhack)
			HFlyhack = HMaxFlyhack;
	}
}
void CheckFlyhack() {
	TestFlying();
	float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
	vars::stuff::max_flyhack = num6;
	if (flyhackDistanceVertical <= num6) {
		vars::stuff::flyhack = flyhackDistanceVertical;
	}

	float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	vars::stuff::max_hor_flyhack = num8;
	if (flyhackDistanceHorizontal <= num8) {
		vars::stuff::hor_flyhack = flyhackDistanceHorizontal;
	}
}
