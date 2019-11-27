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

#include <sm_argbuffer.h>

TEST(ArgBuffer, Size) {
	size_t size = sizeof(int) + sizeof(float) + sizeof(bool) + sizeof(void*);
	ArgBuffer <int, float, bool, void*> buff(3, 4.6f, false, nullptr); 
	
	EXPECT_EQ(size, static_cast<size_t>(buff.size()));
}

TEST(ArgBuffer, Values) {
	ArgBuffer <int, float, bool> buff(3, 1.0f, false); 
	unsigned char *blob = buff;
	
	int a = *((int*)blob);
	blob += sizeof(int);
	EXPECT_EQ(a, 3);
	
	float b = *((float*)blob);
	blob += sizeof(float);
	EXPECT_EQ(b, 1.0f);
	
	bool c = *((bool*)blob);
	blob += sizeof(bool);
	EXPECT_EQ(c, false);
}

TEST(ArgBuffer, StringValue) {
	char test[32] = {"dvander is the bee's bees"};
	ArgBuffer <char[32]> buff(test); 
	
	unsigned char *blob = buff;
	char *str = (char*)blob;
	EXPECT_STREQ(str, test);
}