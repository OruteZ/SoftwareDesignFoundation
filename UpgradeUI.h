#pragma once

#define NUMBER_OF_UPGARDES (6)

typedef enum UpgradeType {
	PotionUpgradeType,
	MaxHPUpgradeType,
	DamageUpgradeType,
	AtkSpeedUpgradeType,
	MoveSpeedUpgradeType,
	BulletUpgradeType,
} UpgradeType;

void StartUpgradeUI();
void UpdateUpgradeUI();
void RenderUpgradeUI();
void ExitUpgradeUI();

int GetUpgradeAmount(UpgradeType upgrade);