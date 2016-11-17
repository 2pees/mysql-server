/* Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

// First include (the generated) my_config.h, to get correct platform defines.
#include "my_config.h"
#include "m_ctype.h"
#include <gtest/gtest.h>

#include "benchmark.h"

namespace strings_valid_check_unittest {
// Benchmark testing character valid check function of utf8 charset
static void BM_UTF8_Valid_Check(size_t num_iterations)
{
  StopBenchmarkTiming();

  const char *content= "MySQL は 1億以上のダウンロード数を誇る、世界"
    "でもっとも普及しているオープンソースデータベースソフトウェアです。"
    "抜群のスピードと信頼性、使いやすさが備わった MySQL は、ダウンタイム"
    "、メンテナンス、管理、サポートに関するさまざまな問題を解決することが"
    "できるため、Web、Web2.0、SaaS、ISV、通信関連企業の 先見的なIT 責任者"
    "の方々から大変な好評を博しています。";
  const int len= strlen(content);
  const CHARSET_INFO *cs= &my_charset_utf8mb4_0900_ai_ci;
  int error= 0;

  StartBenchmarkTiming();
  for (size_t i= 0; i < num_iterations; ++i)
  {
    cs->cset->well_formed_len(cs, content, content + len, len, &error);
  }
  StopBenchmarkTiming();

  ASSERT_EQ(0, error);
}
BENCHMARK(BM_UTF8_Valid_Check);

} // namespace


