#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
    RemoveBuildingForPlayer(playerid, 3777, 831.9609, -1191.1406, 25.0391, 0.25);
    RemoveBuildingForPlayer(playerid, 3777, 868.1328, -1191.1406, 25.0391, 0.25);
    RemoveBuildingForPlayer(playerid, 5926, 816.3359, -1217.1484, 26.4453, 0.25);
    RemoveBuildingForPlayer(playerid, 3777, 902.3359, -1191.1406, 25.0391, 0.25);
    RemoveBuildingForPlayer(playerid, 6005, 895.2578, -1256.9297, 31.2344, 0.25);
    RemoveBuildingForPlayer(playerid, 5836, 816.3359, -1217.1484, 26.4453, 0.25);
    RemoveBuildingForPlayer(playerid, 3776, 831.9609, -1191.1406, 25.0391, 0.25);
    RemoveBuildingForPlayer(playerid, 3776, 868.1328, -1191.1406, 25.0391, 0.25);
    RemoveBuildingForPlayer(playerid, 5838, 895.2578, -1256.9297, 31.2344, 0.25);
    RemoveBuildingForPlayer(playerid, 3776, 902.3359, -1191.1406, 25.0391, 0.25);
    return 1;
}

hook OnGameModeInit()
{
    CreateDynamicObject(11292, 919.71527, -1201.86157, 17.33480,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(3627, 897.26740, -1187.13623, 19.79710,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(17038, 814.96570, -1184.04089, 15.98490,   0.00000, 0.00000, 180.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(3627, 856.28741, -1187.13623, 19.79710,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2165, 919.46301, -1204.29346, 16.12560,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2356, 920.24170, -1205.28906, 16.12720,   0.00000, 0.00000, 45.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2267, 921.75220, -1201.84656, 17.66360,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(11706, 918.63049, -1197.96033, 16.12650,   0.00000, 0.00000, 45.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2309, 921.02557, -1202.89661, 16.12680,   0.00000, 0.00000, 145.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(1893, 919.46838, -1202.36914, 18.85260,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(1893, 920.76440, -1202.29724, 18.85260,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2007, 921.32159, -1198.07483, 16.12640,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2007, 920.34161, -1198.07483, 16.12640,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(19893, 920.76660, -1197.86060, 17.52980,   0.00000, 0.00000, 295.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(3577, 926.76208, -1194.11633, 16.69500,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(930, 928.10992, -1192.00964, 16.44330,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2567, 928.98541, -1175.67444, 17.88760,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2567, 928.98541, -1180.71545, 17.88760,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2973, 928.90399, -1184.64233, 15.96420,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(2973, 928.90399, -1187.20227, 15.96420,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 912.71863, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 902.36761, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 892.08258, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 881.79761, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 871.69958, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 861.41461, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 851.12958, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(983, 840.84460, -1184.50659, 16.65300,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(922, 818.76477, -1190.84106, 16.82710,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(18257, 809.34650, -1205.15369, 15.96670,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    CreateDynamicObject(1623, 919.99652, -1206.29309, 18.09810,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1, 0);
    return 1;
}