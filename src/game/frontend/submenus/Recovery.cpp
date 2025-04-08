#include "Recovery.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping = std::make_shared<Category>("Shopping");
		auto vehiclesGroup = std::make_shared<Group>("Vehicles");
		auto heistGroup = std::make_shared<Group>("Heist");

		vehiclesGroup->AddItem(std::make_shared<BoolCommandItem>("dlcvehicles"_J));

		vehiclesGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
			{
				if (GiveVehicleReward::IsSafeToRunScript())
				{
					GiveVehicleReward::SetShouldRunScript(true);
				}
			}
		}));
		heistGroup->AddItem(std::make_shared<CommandItem>("skipcayosetup"_J));
		heistGroup->AddItem(std::make_shared<CommandItem>("skipcayocooldown"_J));

		shopping->AddItem(vehiclesGroup);

		// Start Currencies Changes
		auto currenciesRP = std::make_shared<Category>("Currencies & PR");
		auto currenciesGroup   = std::make_shared<Group>("Currencies");
		
		currenciesGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Add 10M$"))
			{
				Self::GetPlayer().AddMoney(10000000);
			}
		}));
		currenciesRP->AddItem(currenciesGroup);

		auto RPGroup = std::make_shared<Group>("RP");

		RPGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Add 1K RP"))
			{
				Self::GetPlayer().AddRP(1000);
			}
		}));
		RPGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Add 10K RP"))
			{
				Self::GetPlayer().AddRP(10000);
			}
		}));
		RPGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Add 100K RP"))
			{
				Self::GetPlayer().AddRP(100000);
			}
		}));
		currenciesRP->AddItem(RPGroup);

		heist->AddItem(heistGroup);
		AddCategory(std::move(shopping));
		AddCategory(std::move(heist));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
	}
}