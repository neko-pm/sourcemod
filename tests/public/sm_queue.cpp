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

#include <sm_queue.h>
#include <algorithm>

TEST(Queue, Size) {
	Queue<int> q;
	
	q.push(4);
	q.push(6);
	q.push(8);
	
	EXPECT_EQ(q.size(), 3);
	
	q.clear();
	EXPECT_EQ(q.size(), 0);
	EXPECT_EQ(q.empty(), true);
}

TEST(Queue, Remove) {
	Queue<int> q;
	
	q.push(4);
	q.push(6);
	q.push(8);
	
	q.remove(6);
	
	EXPECT_EQ(q.size(), 2);
}

TEST(Queue, Find) {
	Queue<int> q;
	
	q.push(4);
	q.push(6);
	q.push(8);
	
	auto it = q.find(6);
	
	EXPECT_NE(it, q.end());
}

TEST(Queue, CopyAndPop) {
	Queue<int> q1;
	q1.push(4);
	q1.push(6);
	q1.push(8);
	
	Queue<int> q2 = q1;

	EXPECT_EQ(q2.size(), q1.size());
	EXPECT_EQ(q2.first(), 4);
	q2.pop();
	EXPECT_EQ(q2.first(), 6);
	q2.pop();
	EXPECT_EQ(q2.first(), 8);
	q2.pop();
	EXPECT_EQ(q2.empty(), true);
}