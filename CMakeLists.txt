cmake_minimum_required(VERSION 3.20)

project(RPGDesktop LANGUAGES CXX)

add_executable(RPGTest
	tests/RPGTest.cpp
	src/Character/Character.cpp
	src/Character/Player.cpp
	src/Character/Monster.cpp
	src/World/Map.cpp
	src/Game/Game.cpp
	src/Game/Combat.cpp
	src/Inventory/Item.cpp
	src/Inventory/Inventory.cpp
	src/World/Region.cpp
	src/World/World.cpp
	src/Game/GameState.cpp
	src/Save/SaveManager.cpp
)

target_include_directories(RPGTest PRIVATE include)

target_compile_features(RPGTest PRIVATE cxx_std_23)