#include "pch.h"

namespace railroadtest
{
	TEST(Railroad, Initialize)
	{
		Monopoly m;
		EXPECT_EQ(m.railroads[0].cost, 200);
		EXPECT_EQ(m.railroads[0].is_owned, false);
		EXPECT_EQ(m.railroads[0].railroad_type, nrails::railroad_types::Reading_Railroad);
		EXPECT_EQ(m.railroads[0].name, "Reading_Railroad");

		EXPECT_EQ(m.railroads[1].cost, 200);
		EXPECT_EQ(m.railroads[1].is_owned, false);
		EXPECT_EQ(m.railroads[1].railroad_type, nrails::railroad_types::Pennsylvania_Railroad);
		EXPECT_EQ(m.railroads[1].name, "Pennsylvania_Railroad");

		EXPECT_EQ(m.railroads[2].cost, 200);
		EXPECT_EQ(m.railroads[2].is_owned, false);
		EXPECT_EQ(m.railroads[2].railroad_type, nrails::railroad_types::B_0_Railroad);
		EXPECT_EQ(m.railroads[2].name, "B_0_Railroad");

		EXPECT_EQ(m.railroads[3].cost, 200);
		EXPECT_EQ(m.railroads[3].is_owned, false);
		EXPECT_EQ(m.railroads[3].railroad_type, nrails::railroad_types::Short_Line);
		EXPECT_EQ(m.railroads[3].name, "Short_Line");
	}
}