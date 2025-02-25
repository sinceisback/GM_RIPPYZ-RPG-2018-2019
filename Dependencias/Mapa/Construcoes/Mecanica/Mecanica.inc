#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    CreateDynamicObject(11504, 331.23230, -46.64750, 0.54680,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(983, 314.87231, -44.52430, 1.25460,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(12943, 317.79150, -23.85860, 0.55710,   0.00000, 0.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(983, 334.58591, -31.77690, 1.13860,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(983, 328.20389, -31.77690, 1.13860,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(983, 325.00589, -31.77690, 1.13860,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(19817, 317.82141, -22.53110, 0.57360,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(930, 314.12021, -24.97940, 1.04950,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(2115, 321.28351, -26.90740, 0.57450,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(19893, 321.19788, -26.04260, 1.37293,   0.00000, 0.00000, 297.61044, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(1003, 321.30411, -27.13300, 1.50830,   0.00000, 78.38000, 269.55020, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(1019, 322.02411, -26.24440, 1.42470,   0.10500, 0.25200, 302.77179, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(1020, 321.92169, -26.98450, 1.39280,   -2.50000, 6.00000, 276.39752, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(1098, 321.62119, -26.52890, 1.84640,   0.00000, 0.00000, 180.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(19805, 321.75110, -23.38270, 2.63650,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(3633, 314.74579, -31.18850, 1.01090,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(1098, 314.69989, -30.39310, 1.04640,   0.00000, 0.00000, 89.59500, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(2356, 320.51685, -25.74764, 0.57530,   0.00000, 0.00000, 154.90895, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(1010, 314.05200, -25.53500, 0.66050,   0.00000, 90.00000, 270.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(2567, 323.02429, -25.35810, 2.51830,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(10281, 331.38739, -58.38890, 2.27530,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(922, 313.25110, -25.02100, 1.43210,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(3632, 313.30450, -27.74170, 1.04610,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(1098, 314.69989, -31.20910, 1.93040,   0.00000, 0.00000, 45.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(11711, 313.85959, -18.08570, 3.00840,   0.00000, 0.00000, 90.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(14687, 316.00000, 9599.00000, -19.00000,   0.00000, 0.00000, 0.00000, -1, 0, -1, 350.0, 350.0, -1);
    CreateDynamicObject(14687, 320.31769, -19.25941, 4.42640,   0.00000, 0.00000, 90.34950, -1, 0, -1, 350.0, 350.0, -1);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    RemoveBuildingForPlayer(playerid, 13063, 321.8516, -34.5234, 4.8984, 0.25);
    RemoveBuildingForPlayer(playerid, 1440, 308.7891, -54.6875, 1.0625, 0.25);
    RemoveBuildingForPlayer(playerid, 1684, 317.6953, -42.2344, 2.0156, 0.25);
    RemoveBuildingForPlayer(playerid, 13061, 321.8516, -34.5234, 4.8984, 0.25);
    return 1;
}