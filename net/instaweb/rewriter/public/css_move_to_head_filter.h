/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */


#ifndef NET_INSTAWEB_REWRITER_PUBLIC_CSS_MOVE_TO_HEAD_FILTER_H_
#define NET_INSTAWEB_REWRITER_PUBLIC_CSS_MOVE_TO_HEAD_FILTER_H_

#include "net/instaweb/rewriter/public/common_filter.h"
#include "net/instaweb/rewriter/public/rewrite_driver.h"
#include "pagespeed/kernel/base/basictypes.h"
#include "pagespeed/kernel/html/html_element.h"

namespace net_instaweb {

class Statistics;
class Variable;

// Moves all CSS <link> and <style> tags either into the bottom of the <head>
// or above the first <script> depending on settings.
class CssMoveToHeadFilter : public CommonFilter {
 public:
  explicit CssMoveToHeadFilter(RewriteDriver* driver);
  virtual ~CssMoveToHeadFilter();

  static void InitStats(Statistics* statistics);

  virtual void StartDocumentImpl();
  virtual void StartElementImpl(HtmlElement* element) {}
  virtual void EndElementImpl(HtmlElement* element);

  virtual const char* Name() const { return "CssMoveToHead"; }

 private:
  // Should we move CSS into head? If not, we just move it above scripts.
  bool move_css_to_head_;
  // Should we move CSS above scripts? If not, we just move CSS to the bottom
  // of the head element.
  bool move_css_above_scripts_;

  HtmlElement* move_to_element_;
  bool element_is_head_;

  Variable* css_elements_moved_;

  DISALLOW_COPY_AND_ASSIGN(CssMoveToHeadFilter);
};

}  // namespace net_instaweb

#endif  // NET_INSTAWEB_REWRITER_PUBLIC_CSS_MOVE_TO_HEAD_FILTER_H_
