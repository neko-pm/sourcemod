/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Test Suite
 * Copyright (C) 2019 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include <gtest/gtest.h>

#include <CDataPack.h>

TEST(CDataPack, StartPosition) {
	CDataPack pack;
	
	EXPECT_EQ(pack.GetPosition(), 0);
}

TEST(CDataPack, PositionOOB) {
	CDataPack pack;
	bool res = pack.SetPosition(3);
	EXPECT_EQ(res, false);
}

TEST(CDataPack, EmptyReadable) {
	CDataPack pack;
	bool res = pack.IsReadable();
	EXPECT_EQ(res, false);
}

TEST(CDataPack, PackAndReadCell) {
	CDataPack pack;

	pack.PackCell(43);
	pack.Reset();
	auto ret = pack.ReadCell();
	EXPECT_EQ(ret, 43);
}

TEST(CDataPack, PackAndReadFunction) {
	CDataPack pack;

	pack.PackFunction(43);
	pack.Reset();
	auto ret = pack.ReadFunction();
	EXPECT_EQ(ret, 43);
}

TEST(CDataPack, PackAndReadFloat) {
	CDataPack pack;

	pack.PackFloat(1.0f);
	pack.Reset();
	auto ret = pack.ReadFloat();
	EXPECT_EQ(ret, 1.0f);
}

TEST(CDataPack, PackAndReadString) {
	CDataPack pack;

	constexpr const char *str = ":D";
	pack.PackString(str);
	pack.Reset();
	
	size_t len;
	const char* ret = pack.ReadString(&len);
	EXPECT_STREQ(ret, str);
}

TEST(CDataPack, RemoveItem) {
	CDataPack pack;

	pack.PackCell(43);
	pack.RemoveItem(0);
	pack.Reset();
	bool res = pack.IsReadable();
	EXPECT_EQ(res, false);
}

TEST(CDataPack, Clear) {
	CDataPack pack;

	for (int i = 0; i < 10; i++)
		pack.PackCell(43);

	pack.ResetSize();
	bool res = pack.IsReadable();
	EXPECT_EQ(res, false);
}
