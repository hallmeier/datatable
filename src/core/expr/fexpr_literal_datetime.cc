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

FExpr_Literal_Datetime::FExpr_Literal_Datetime(int64_t x)
  : value_(x) {}


ptrExpr FExpr_Literal_Datetime::make(py::robj src) {
  py::odatetime src_datetime = src.to_odatetime();
  return ptrExpr(new FExpr_Literal_Datetime(src_datetime.get_time()));
}


//------------------------------------------------------------------------------
// Evaluators
//------------------------------------------------------------------------------

Workframe FExpr_Literal_Datetime::evaluate_n(EvalContext& ctx) const {
  return Workframe(ctx, Const_ColumnImpl::make_int_column(1, value_, SType::TIME64));
}


// A datetime is used as a replacement target. This is valid
// only if `j` column(s) have stype TIME64.
//
//   DT[:, j] = datetime.datetime(2024, 9, 10, 12, 35, 42)
//
Workframe FExpr_Literal_Datetime::evaluate_r(EvalContext& ctx, const sztvec&) const
{
  return Workframe(ctx, Const_ColumnImpl::make_int_column(1, value_, SType::TIME64));
}


Workframe FExpr_Literal_Datetime::evaluate_f(EvalContext&, size_t) const
{
  throw TypeError()
    << "A datetime cannot be used as a column selector";
}



Workframe FExpr_Literal_Datetime::evaluate_j(EvalContext&) const
{
  throw TypeError()
    << "A datetime cannot be used as a column selector";
}


RowIndex FExpr_Literal_Datetime::evaluate_i(EvalContext&) const {
  throw TypeError() << "A datetime cannot be used as a row selector";
}


RiGb FExpr_Literal_Datetime::evaluate_iby(EvalContext&) const {
  throw TypeError() << "A datetime cannot be used as a row selector";
}


//------------------------------------------------------------------------------
// Other methods
//------------------------------------------------------------------------------

Kind FExpr_Literal_Datetime::get_expr_kind() const {
  return Kind::Datetime;
}


int FExpr_Literal_Datetime::precedence() const noexcept {
  return 18;
}


std::string FExpr_Literal_Datetime::repr() const {
  char ch[30];
  char* pch = ch;
  time64_toa(&pch, value_);
  return std::string(ch, pch - ch);
}


}}  // namespace dt::expr
