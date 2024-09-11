//------------------------------------------------------------------------------
// Copyright 2019-2020 H2O.ai
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//------------------------------------------------------------------------------
#include "column/const.h"
#include "csv/toa.h"
#include "expr/eval_context.h"
#include "expr/fexpr_literal.h"
#include "expr/workframe.h"
namespace dt {
namespace expr {


//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------

FExpr_Literal_Date::FExpr_Literal_Date(py::odate x)
  : value_(x) {}


ptrExpr FExpr_Literal_Date::make(py::robj src) {
  py::odate src_date = src.to_odate();
  return ptrExpr(new FExpr_Literal_Date(src_date));
}


//------------------------------------------------------------------------------
// Evaluators
//------------------------------------------------------------------------------

Workframe FExpr_Literal_Date::evaluate_n(EvalContext& ctx) const {
  return Workframe(ctx, Const_ColumnImpl::make_int_column(1, value_.get_days(), SType::DATE32));
}


// A date is used as a replacement target. This is valid
// only if `j` column(s) have stype DATE32.
//
//   DT[:, j] = datetime.date(2024, 9, 10)
//
Workframe FExpr_Literal_Date::evaluate_r(EvalContext& ctx, const sztvec&) const
{
  return Workframe(ctx, Const_ColumnImpl::make_int_column(1, value_.get_days(), SType::DATE32));
}


Workframe FExpr_Literal_Date::evaluate_f(EvalContext&, size_t) const
{
  throw TypeError()
    << "A date cannot be used as a column selector";
}



Workframe FExpr_Literal_Date::evaluate_j(EvalContext&) const
{
  throw TypeError()
    << "A date cannot be used as a column selector";
}


RowIndex FExpr_Literal_Date::evaluate_i(EvalContext&) const {
  throw TypeError() << "A date cannot be used as a row selector";
}


RiGb FExpr_Literal_Date::evaluate_iby(EvalContext&) const {
  throw TypeError() << "A date cannot be used as a row selector";
}


//------------------------------------------------------------------------------
// Other methods
//------------------------------------------------------------------------------

Kind FExpr_Literal_Date::get_expr_kind() const {
  return Kind::Date;
}


int FExpr_Literal_Date::precedence() const noexcept {
  return 18;
}


std::string FExpr_Literal_Date::repr() const {
  char ch[11];
  char* pch = ch;
  date32_toa(&pch, value_.get_days());
  return std::string(ch);
}


}}  // namespace dt::expr
