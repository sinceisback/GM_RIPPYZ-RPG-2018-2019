#include <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    new JLKASLIKADLIJKAS[91];

    JLKASLIKADLIJKAS[19] = CreateDynamicObject(1569, 2147.0593, 1604.6702, 1005.3891, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //ADAM_V_DOOR
    JLKASLIKADLIJKAS[20] = CreateDynamicObject(1569, 2149.8906, 1602.1118, 1001.2173, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //ADAM_V_DOOR
    JLKASLIKADLIJKAS[21] = CreateDynamicObject(1569, 2149.8906, 1602.1118, 1001.2479, 0.0000, 90.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //ADAM_V_DOOR
    JLKASLIKADLIJKAS[22] = CreateDynamicObject(1569, 2149.0109, 1604.8220, 1001.2173, 0.0000, 0.0000, 180.0000, 1064, 1, -1, 190.0, 190.0, -1); //ADAM_V_DOOR
    JLKASLIKADLIJKAS[23] = CreateDynamicObject(1569, 2149.0109, 1604.8220, 1001.2276, 0.0000, 90.0000, 180.0000, 1064, 1, -1, 190.0, 190.0, -1); //ADAM_V_DOOR
    JLKASLIKADLIJKAS[24] = CreateDynamicObject(1569, 2147.0593, 1604.6702, 1005.4274, 0.0000, 90.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //ADAM_V_DOOR
    JLKASLIKADLIJKAS[25] = CreateDynamicObject(19273, 2136.1093, 1606.7701, 994.2933, 0.0000, 0.0000, 180.0000, 1064, 1, -1, 190.0, 190.0, -1); //KeypadNonDynamic
    JLKASLIKADLIJKAS[26] = CreateDynamicObject(1550, 2143.2819, 1634.4803, 992.9323, 0.0000, 0.0000, 96.8999, 1064, 1, -1, 190.0, 190.0, -1); //CJ_MONEY_BAG
    JLKASLIKADLIJKAS[27] = CreateDynamicObject(19922, 2144.1752, 1635.7946, 992.5338, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //MKTable1
    SetDynamicObjectMaterial(JLKASLIKADLIJKAS[27], 0, 10765, "airportgnd_sfse", "white", 0xFFFFFFFF);
    JLKASLIKADLIJKAS[28] = CreateDynamicObject(19941, 2144.1672, 1634.4379, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[29] = CreateDynamicObject(19941, 2144.1672, 1634.5080, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[30] = CreateDynamicObject(19941, 2144.1672, 1634.5781, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[31] = CreateDynamicObject(19941, 2144.1672, 1634.6481, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[32] = CreateDynamicObject(19941, 2144.1672, 1634.7182, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[33] = CreateDynamicObject(19941, 2144.1672, 1634.7883, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[34] = CreateDynamicObject(19941, 2144.1672, 1634.8583, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[35] = CreateDynamicObject(19941, 2144.3374, 1634.8583, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[36] = CreateDynamicObject(19941, 2144.3374, 1634.7883, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[37] = CreateDynamicObject(19941, 2144.3374, 1634.7182, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[38] = CreateDynamicObject(19941, 2144.3374, 1634.6481, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[39] = CreateDynamicObject(19941, 2144.3374, 1634.5781, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[40] = CreateDynamicObject(19941, 2144.3374, 1634.5080, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[41] = CreateDynamicObject(19941, 2144.3374, 1634.4379, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[42] = CreateDynamicObject(19941, 2143.9970, 1634.4379, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[43] = CreateDynamicObject(19941, 2143.9970, 1634.5080, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[44] = CreateDynamicObject(19941, 2143.9970, 1634.5781, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[45] = CreateDynamicObject(19941, 2143.9970, 1634.6481, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[46] = CreateDynamicObject(19941, 2143.9970, 1634.7182, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[47] = CreateDynamicObject(19941, 2143.9970, 1634.7883, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[48] = CreateDynamicObject(19941, 2143.9970, 1634.8583, 993.3255, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[49] = CreateDynamicObject(19941, 2144.1672, 1634.5080, 993.3756, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[50] = CreateDynamicObject(19941, 2144.1672, 1634.5781, 993.3756, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[51] = CreateDynamicObject(19941, 2144.1672, 1634.6481, 993.3756, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[52] = CreateDynamicObject(19941, 2144.1672, 1634.7182, 993.3756, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[53] = CreateDynamicObject(19941, 2144.1672, 1634.7883, 993.3756, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[54] = CreateDynamicObject(19941, 2144.1672, 1634.7182, 993.4157, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[55] = CreateDynamicObject(19941, 2144.1672, 1634.6481, 993.4157, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[56] = CreateDynamicObject(19941, 2144.1672, 1634.5781, 993.4157, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[57] = CreateDynamicObject(19941, 2144.1669, 1634.6403, 993.4557, 0.0000, 0.0000, -26.4000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[58] = CreateDynamicObject(19941, 2143.9970, 1634.5480, 993.3656, 0.0000, 0.0000, 54.5999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[59] = CreateDynamicObject(19941, 2144.0053, 1634.7641, 993.3656, 0.0000, 0.0000, -61.3000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[60] = CreateDynamicObject(19941, 2144.3371, 1634.6375, 993.3656, 0.0000, 0.0000, -66.7999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[61] = CreateDynamicObject(1550, 2143.2246, 1634.9466, 992.9323, 0.0000, 0.0000, 4.9999, 1064, 1, -1, 190.0, 190.0, -1); //CJ_MONEY_BAG
    JLKASLIKADLIJKAS[62] = CreateDynamicObject(1550, 2142.9008, 1634.6557, 992.9323, 0.0000, 0.0000, 79.6999, 1064, 1, -1, 190.0, 190.0, -1); //CJ_MONEY_BAG
    JLKASLIKADLIJKAS[63] = CreateDynamicObject(1210, 2144.1879, 1635.4239, 993.4263, 90.0000, 42.1000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //briefcase
    JLKASLIKADLIJKAS[64] = CreateDynamicObject(1210, 2144.1728, 1635.8642, 993.4263, 90.0000, -165.5000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //briefcase
    JLKASLIKADLIJKAS[65] = CreateDynamicObject(19941, 2144.2673, 1635.4790, 993.3956, 0.0000, 0.0000, -98.6999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[66] = CreateDynamicObject(19941, 2144.0769, 1635.3461, 993.3956, 0.0000, 0.0000, -39.7999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[67] = CreateDynamicObject(19941, 2144.2048, 1635.8906, 993.3956, 0.0000, 0.0000, 5.5000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[68] = CreateDynamicObject(19941, 2144.0268, 1635.8543, 993.3956, 0.0000, 0.0000, 119.3999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[69] = CreateDynamicObject(19941, 2144.5856, 1635.6228, 993.3255, 0.0000, 0.0000, 155.5000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[70] = CreateDynamicObject(19941, 2143.7395, 1635.7427, 993.3255, 0.0000, 0.0000, 134.1999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[71] = CreateDynamicObject(19941, 2143.7626, 1635.4178, 993.3255, 0.0000, 0.0000, 88.5999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[72] = CreateDynamicObject(19941, 2144.5576, 1635.1982, 993.3255, 0.0000, 0.0000, 121.2000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[73] = CreateDynamicObject(1550, 2144.0197, 1636.6170, 993.7119, 0.0000, 0.0000, 157.0999, 1064, 1, -1, 190.0, 190.0, -1); //CJ_MONEY_BAG
    JLKASLIKADLIJKAS[74] = CreateDynamicObject(1550, 2144.4929, 1636.9379, 993.7119, 0.0000, 0.0000, -70.0000, 1064, 1, -1, 190.0, 190.0, -1); //CJ_MONEY_BAG
    JLKASLIKADLIJKAS[75] = CreateDynamicObject(19941, 2144.4538, 1636.5323, 993.3255, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[76] = CreateDynamicObject(19941, 2144.3837, 1636.5323, 993.3255, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[77] = CreateDynamicObject(19941, 2144.3137, 1636.5323, 993.3255, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[78] = CreateDynamicObject(19941, 2144.3837, 1636.5323, 993.3656, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[79] = CreateDynamicObject(19941, 2143.7390, 1636.9571, 993.3255, 0.0000, 0.0000, 39.9000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[80] = CreateDynamicObject(19941, 2144.0246, 1637.0668, 993.3255, 0.0000, 0.0000, 95.1000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[81] = CreateDynamicObject(19941, 2143.6418, 1636.4099, 993.3255, 0.0000, 0.0000, 41.2000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[82] = CreateDynamicObject(1829, 2144.2263, 1642.3177, 993.0455, 0.0000, 0.0000, 0.0000, 1064, 1, -1, 190.0, 190.0, -1); //man_safenew
    JLKASLIKADLIJKAS[83] = CreateDynamicObject(19941, 2144.4465, 1642.7807, 993.5200, 0.0000, 0.0000, -48.4000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[84] = CreateDynamicObject(19941, 2144.1066, 1642.7871, 993.5200, 0.0000, 0.0000, -12.4000, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[85] = CreateDynamicObject(19941, 2144.2770, 1642.6269, 993.5200, 0.0000, 0.0000, 60.6999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[86] = CreateDynamicObject(19941, 2144.2470, 1642.9416, 993.5200, 0.0000, 0.0000, 60.6999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[87] = CreateDynamicObject(19941, 2143.9960, 1642.6390, 993.5200, 0.0000, 0.0000, 28.6999, 1064, 1, -1, 190.0, 190.0, -1); //GoldBar1
    JLKASLIKADLIJKAS[88] = CreateDynamicObject(19431, 2144.2067, 1643.1501, 994.5130, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //wall071
    SetDynamicObjectMaterialText(JLKASLIKADLIJKAS[88], 0, "COFRE", 90, "Arial Black", 44, 1, 0xFFFFFFFF, 0x0, 0);
    JLKASLIKADLIJKAS[89] = CreateDynamicObject(19431, 2144.7873, 1643.1501, 993.3425, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //wall071
    SetDynamicObjectMaterialText(JLKASLIKADLIJKAS[89], 0, "R", 90, "Arial Black", 44, 1, 0xFFFFFFFF, 0x0, 0);
    JLKASLIKADLIJKAS[90] = CreateDynamicObject(19431, 2144.9174, 1643.1401, 992.9726, 0.0000, 0.0000, 90.0000, 1064, 1, -1, 190.0, 190.0, -1); //wall071
    SetDynamicObjectMaterialText(JLKASLIKADLIJKAS[90], 0, "C", 90, "Arial Black", 44, 1, 0xFFFFFFFF, 0x0, 0);
    return 1;
}