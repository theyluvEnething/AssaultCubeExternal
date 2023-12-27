#pragma once
#include <Windows.h>
#include <vector>


namespace offset {
	const DWORD ammoAddr = 0x17E0A8;
	const std::vector<DWORD> ammoOffsets = { 0x368, 0x14, 0x0 };

	const DWORD recoilAddr = 0x17E0A8;
	const std::vector<DWORD> recoilOffsets01{ 0x364, 0xC, 0x5E };
	const std::vector<DWORD> recoilOffsets02{ 0x364, 0xC, 0x60 };


	const DWORD localplayer = 0x0017E0A8;
	const DWORD entitylist = 0x00191FCC;

	const DWORD entityDistance = 0x4;
	const DWORD entityHealth = 0xEC ; // 0x4 between every entity
	const DWORD entityName = 0x205;
	const DWORD entityPosX = 0x4; // north-south
	const DWORD entityPosY = 0x8; // west-ost
	const DWORD entityPosZ = 0xC; // height

	// ac_client.exe+18AC0C -> 0058AC0C
	const DWORD uEntityCount = 0x0058AC0C; // length of entity list 

	const DWORD iViewMatrix = 0x57DFD0;

	const DWORD iGameWidth = 0x591ED8;
	const DWORD iGameHeight = 0x591EDC;
}