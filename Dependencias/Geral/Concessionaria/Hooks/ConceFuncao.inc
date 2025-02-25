#include <YSI_Coding\y_hooks>

enum VeiculOS
{
    Modelo,
    Valor,
    Nome[128],
    Categoria[128],
    TypeVehic
};

new ConceModelos[][VeiculOS] =
{
    {400, 50000, "Landstalker", "Off Road", 0}, 
    {401, 75000, "Bravura", "Saloons", 0},
    {402, 90000, "Buffalo", "Sport Vehicles", 1},
    {404, 30000, "Perennial", "Station Wagons", 0},
    {405, 40000, "Sentinel", "Saloons", 0},
    {409, 95000, "Stretch", "Unique Vehicles", 0},
    {410, 50000, "Manana", "Saloons", 0},
    {411, 220000, "Infernus", "Sport Vehicles", 1},
    {412, 70000, "Voodoo", "Lowriders", 2},
    {415, 190000, "Cheetah", "Sport Vehicles", 1},
    {418, 80000, "Moonbeam", "Station Wagons", 0},
    {419, 80000, "Esperanto", "Saloons", 0},
    {421, 60000, "Washington", "Saloons", 0},
    {422, 60000, "Bobcat", "Industrial", 3},
    {423, 80000, "Mr. Whoopee", "Unique Vehicles", 0},
    {424, 60000, "BF Injection", "Off Road", 0},
    {426, 60000, "Premier", "Saloons", 0},
    {429, 190000, "Banshee", "Sport Vehicles", 1},
    {434, 120000, "Hotknife", "Unique Vehicles", 0},
    {436, 70000, "Previon", "Saloons", 0},
    {437, 450000, "Coach", "Public Service"},
    {439, 80000, "Stallion", "Convertibles", 0},
    {440, 62000, "Rumpo", "Industrial", 3},
    {442, 79000, "Romero", "Unique Vehicles", 0},
    {443, 200000, "Packer", "Industrial", 3},
    {444, 110000, "Monster", "Off Road", 0},
    {445, 70000, "Admiral", "Saloons", 0},
    {451, 200000, "Turismo", "Sport Vehicles", 1},
    {455, 110000, "Flatbed", "Industrial", 3},
    {457, 20000, "Caddy", "Unique Vehicles", 0},
    {458, 30000, "Solair", "Station Wagons", 0},
    {462, 4000, "Faggio", "Bikes", 0},
    {463, 80000, "Freeway", "Bikes", 0},
    {466, 68000, "Glendale", "Saloons", 0},
    {467, 69000, "Oceanic", "Saloons", 0},
    {468, 9000, "Sanchez", "Bikes", 0},
    {471, 45000, "Quad", "Bikes", 0},
    {474, 59000, "Hermes", "Saloons", 0},
    {475, 125000, "Sabre", "Sport Vehicles", 1},
    {477, 130000, "ZR-350", "Sport Vehicles", 1},
    {480, 95000, "Comet", "Convertibles", 1},
    {481, 2000, "BMX", "Bikes", 0},
    {483, 90000, "Camper", "Unique Vehicles", 0},
    {489, 85000, "Rancher", "Off Road", 0},
    {491, 89000, "Virgo", "Saloons", 0},
    {492, 60000, "Greenwood", "Saloons", 0},
    {494, 150000, "Hotring Racer", "Sport Vehicles", 1},
    {495, 70000, "Sandking", "Off Road", 0},
    {496, 30000, "Blista Compact", "Sport Vehicles", 1},
    {500, 75000, "Mesa", "Off Road", 0},
    {502, 120000, "Hotring Racer A", "Sport Vehicles", 1},
    {503, 120000, "Hotring Racer B", "Sport Vehicles", 1},
    {504, 95000, "Bloodring Banger", "Saloons", 0},
    {506, 190000, "Super GT", "Sport Vehicles", 1},
    {508, 250000, "Trailer Ben-10", "Easter Egg"},
    {509, 1000, "Bike", "Bike", 0},
    {510, 1300, "Mountain Bike", "Bike", 0},
    {517, 58000, "Majestic", "Saloons", 0},
    {521, 70000, "FCR-900", "Bikes", 0},
    {522, 90000, "NRG-500", "Bikes", 0},
    {526, 65000, "Fortune", "Saloons", 0},
    {527, 52000, "Cadrona", "Saloons", 0},
    {529, 50000, "Willard", "Saloons", 0},
    {533, 52000, "Feltzer", "Convertibles", 0},
    {534, 50000, "Remington", "Lowriders", 2},
    {535, 70000, "Slamvan", "Lowriders", 2},
    {536, 70000, "Blade", "Lowriders", 2},
    {540, 75000, "Vincent", "Saloons", 0},
    {541, 190000, "Bullet", "Sport Vehicles", 1},
    {542, 74000, "Clover", "Sport Vehicles", 1},
    {543, 55000, "Sadler", "Industrial", 3},
    {545, 75000, "Hustler", "Unique Vehicles", 0},
    {546, 45000, "Intruder", "Saloons", 0},
    {547, 45000, "Primo", "Saloons", 0},
    {550, 85000, "Sunrise", "Saloons", 0},
    {551, 40000, "Merit", "Saloons", 0},
    {554, 58000, "Yosemite", "Industrial", 3},
    {555, 100000, "Windsor", "Convertibles", 0},
    {556, 125000, "Monster A", "Off Road", 0},
    {557, 128000, "Monster B", "Off Road", 0},
    {558, 110000, "Uranus", "Sport Vehicles", 1},
    {559, 100000, "Jester", "Sport Vehicles", 1},
    {560, 110000, "Sultan", "Saloons", 0},
    {561, 110000, "Stratum", "Station Wagons", 0},
    {562, 100000, "Elegy", "Saloons", 0},
    {565, 90000, "Flash", "Sport Vehicles", 1},
    {566, 80000, "Tahoma", "Lowriders", 2},
    {567, 80000, "Savanna", "Lowriders", 2},
    {568, 80000, "Bandito", "Off Road", 0},
    {571, 20000, "Kart", "Unique Vehicles", 0},
    {572, 20000, "Mower", "Unique Vehicles", 0},
    {573, 80000, "Dune", "Off Road", 0},
    {575, 50000, "Broadway", "Lowriders", 2},
    {576, 70000, "Tornado", "Lowriders", 2},
    {579, 60000, "Huntley", "Off Road", 0},
    {580, 85000, "Stafford", "Saloons", 0},
    {581, 20000, "BF-400", "Bikes", 0},
    {586, 80000, "Wayfarer", "Bikes", 0},
    {585, 60000, "Emperor", "Saloons", 0},
    {587, 89000, "Euros", "Sport Vehicles", 1},
    {589, 60000, "Club", "Sport Vehicles", 1},
    {600, 80000, "Picador", "Industrial", 3},
    {603, 90000, "Phoenix", "Sport Vehicles", 1},
    {602, 80000, "Alpha", "Sport Vehicles", 1},

    // Avi�es
    {511, 350000, "Beagle", "AirPlane", 5},
    {513, 250000, "Stuntplane", "AirPlane", 5},
    {519, 8000000, "Shamal", "AirPlane", 5},
    {593, 200000, "Dodo", "AirPlane", 5},

    // Helic�pteros
    {417, 750000, "Levianthan", "Helicopters", 4},
    {487, 650000, "Maverick", "Helicopters", 4},
    //{447, 350000, "Seasparrow", "Helicopters", 4},
    {469, 380000, "Sparrow", "Helicopters", 4}
};