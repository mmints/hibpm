// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.



// First part of user prologue.
#line 12 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"

#include <iostream>
#include <string>
#include "../DeclareContext.hpp"
#include "location.hh" // This is said by the generated files

// Turns a char* (in this case yytext) into a string and removes all unecessary chars following by the value.
std::string convertCharToString(const std::string &delimiter, char *s)
{
    std::string input(s); // Construct String from Char
    return input.substr(0, input.find(delimiter));
}


#line 56 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"


#include "declare-parser.hpp"

// Second part of user prologue.
#line 70 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"

extern int yylex(yy::declare::semantic_type *yylval, // Custom yylex declaration
        yy::declare::location_type* yylloc,
        hibpm::DeclareContext &declare_ctx);

#line 68 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"



#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 161 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"

  /// Build a parser object.
  declare::declare (hibpm::DeclareContext &declare_ctx_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      declare_ctx (declare_ctx_yyarg)
  {}

  declare::~declare ()
  {}

  declare::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  declare::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  declare::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  declare::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  declare::symbol_kind_type
  declare::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  declare::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  declare::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  declare::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  declare::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  declare::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  declare::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  declare::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  declare::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  declare::symbol_kind_type
  declare::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  declare::symbol_kind_type
  declare::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  declare::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  declare::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  declare::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  declare::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  declare::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  declare::symbol_kind_type
  declare::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  declare::stack_symbol_type::stack_symbol_type ()
  {}

  declare::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  declare::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  declare::stack_symbol_type&
  declare::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  declare::stack_symbol_type&
  declare::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  declare::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  declare::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  declare::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  declare::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  declare::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  declare::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  declare::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  declare::debug_level_type
  declare::debug_level () const
  {
    return yydebug_;
  }

  void
  declare::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  declare::state_type
  declare::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  declare::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  declare::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  declare::operator() ()
  {
    return parse ();
  }

  int
  declare::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 76 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
{
// Filename for locations here
yyla.location.begin.filename = yyla.location.end.filename = new std::string("stdin");
}

#line 500 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location, declare_ctx));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 4: // rule: PARTICIPATION OP QUOTE VAR QUOTE CL EOL
#line 89 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                              { std::string val = convertCharToString("'", (yystack_[3].value.event_name_val));
                                                declare_ctx.addUnaryConstraintData(hibpm::PARTICIPATION, val);
                                              }
#line 640 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 5: // rule: AT_MOST_ONE OP QUOTE VAR QUOTE CL EOL
#line 94 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                            { std::string val = convertCharToString("'", (yystack_[3].value.event_name_val));
                                                declare_ctx.addUnaryConstraintData(hibpm::AT_MOST_ONE, val);
                                              }
#line 648 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 6: // rule: AT_MOST_TWO OP QUOTE VAR QUOTE CL EOL
#line 99 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                            { std::string val = convertCharToString("'", (yystack_[3].value.event_name_val));
                                                std::cout << "#### !TODO! atMost2 ####" << std::endl;
                                              }
#line 656 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 7: // rule: AT_MOST_THREE OP QUOTE VAR QUOTE CL EOL
#line 104 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                              { std::string val = convertCharToString("'", (yystack_[3].value.event_name_val));
                                                std::cout << "#### !TODO! atMost3 ####" << std::endl;
                                              }
#line 664 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 8: // rule: AT_LEAST_ONE OP QUOTE VAR QUOTE CL EOL
#line 109 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                             { std::string val = convertCharToString("'", (yystack_[3].value.event_name_val));
                                                std::cout << "#### !TODO! atLeast1 ####" << std::endl;
                                              }
#line 672 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 9: // rule: INIT OP QUOTE VAR QUOTE CL EOL
#line 114 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                     { std::string val = convertCharToString("'", (yystack_[3].value.event_name_val));
                                                declare_ctx.addUnaryConstraintData(hibpm::INIT, val);
                                              }
#line 680 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 10: // rule: END OP QUOTE VAR QUOTE CL EOL
#line 119 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                    { std::string val = convertCharToString("'", (yystack_[3].value.event_name_val));
                                                declare_ctx.addUnaryConstraintData(hibpm::END, val);
                                              }
#line 688 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 11: // rule: RESPONDED_EXISTENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 126 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                          { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::RESPONDED_EXISTENCE, val_1, val_2);
                                                                          }
#line 697 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 12: // rule: RESPONSE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 132 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                               { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::RESPONSE, val_1, val_2);
                                                                          }
#line 706 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 13: // rule: ALTERNATED_RESPONSE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 138 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                          { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::ALTERNATED_RESPONSE, val_1, val_2);
                                                                          }
#line 715 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 14: // rule: CHAIN_RESPONSE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 144 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                     { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::CHAIN_RESPONSE, val_1, val_2);
                                                                          }
#line 724 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 15: // rule: PRECEDENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 150 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                 { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::PRECEDENCE, val_1, val_2);
                                                                          }
#line 733 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 16: // rule: ALTERNATED_PRECEDENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 156 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                            { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::ALTERNATED_PRECEDENCE, val_1, val_2);
                                                                          }
#line 742 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 17: // rule: CHAIN_PRECEDENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 162 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                       { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::CHAIN_PRECEDENCE, val_1, val_2);
                                                                          }
#line 751 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 18: // rule: CO_EXISTENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 168 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                   { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::CO_EXISTENCE, val_1, val_2);
                                                                          }
#line 760 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 19: // rule: SUCCESSION OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 174 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                 { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::SUCCESSION, val_1, val_2);
                                                                          }
#line 769 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 20: // rule: ALTERNATED_SUCCESSION OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 180 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                            { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::ALTERNATED_SUCCESSION, val_1, val_2);
                                                                          }
#line 778 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 21: // rule: CHAIN_SUCCESSION OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 186 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                       { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::CHAIN_SUCCESSION, val_1, val_2);
                                                                          }
#line 787 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 22: // rule: NOT_CHAIN_SUCCESSION OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 192 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                           { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::NOT_CHAIN_SUCCESSION, val_1, val_2);
                                                                          }
#line 796 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 23: // rule: NOT_SUCCESSION OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 198 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                     { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::NOT_SUCCESSION, val_1, val_2);
                                                                          }
#line 805 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;

  case 24: // rule: NOT_CO_EXISTENCE OP QUOTE VAR QUOTE COMMA QUOTE VAR QUOTE CL EOL
#line 204 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"
                                                                       { std::string val_1 = convertCharToString("'",(yystack_[7].value.event_name_val));
                                                                            std::string val_2 = convertCharToString("'",(yystack_[3].value.event_name_val));
                                                                            declare_ctx.addBinaryConstraintData(hibpm::NOT_CO_EXISTENCE, val_1, val_2);
                                                                          }
#line 814 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"
    break;


#line 818 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  declare::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  declare::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char declare::yypact_ninf_ = -24;

  const signed char declare::yytable_ninf_ = -1;

  const short
  declare::yypact_[] =
  {
      21,   -23,   -22,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,   -24,    19,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,   -24,    21,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24
  };

  const signed char
  declare::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     4,     5,     6,     7,     8,     9,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24
  };

  const short
  declare::yypgoto_[] =
  {
     -24,   222,   -24
  };

  const signed char
  declare::yydefgoto_[] =
  {
       0,    46,    23
  };

  const unsigned char
  declare::yytable_[] =
  {
      45,    24,    25,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    47,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,     0,     0,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,     0,     0,     0,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,     0,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,     0,     0,     0,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,    22,     0,     0,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207
  };

  const signed char
  declare::yycheck_[] =
  {
       0,    24,    24,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    26,    24,    24,    24,    24,
      24,    24,    24,    24,    24,    24,    24,    24,    24,    24,
      24,    24,    24,    24,    24,    -1,    -1,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    -1,    -1,    -1,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    25,    25,    25,    25,    25,    25,    25,    -1,
      -1,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    27,    27,    -1,    28,    28,    28,    28,
      28,    28,    28,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    -1,    -1,    -1,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    25,    25,
      25,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,    25,     0,    -1,    -1,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,    28,    28
  };

  const signed char
  declare::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    31,    32,    24,    24,    24,    24,    24,    24,
      24,    24,    24,    24,    24,    24,    24,    24,    24,    24,
      24,    24,    24,    24,    24,     0,    31,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    29,    29,    29,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      25,    25,    25,    25,    25,    25,    25,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    28,    28,    28,    28,    28,    28,    28,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      26,    26,    29,    29,    29,    29,    29,    29,    29,    29,
      29,    29,    29,    29,    29,    29,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,    26,    26,    26,    26,
      25,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,    25,    25,    25,    28,    28,    28,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,    28
  };

  const signed char
  declare::yyr1_[] =
  {
       0,    30,    31,    31,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32
  };

  const signed char
  declare::yyr2_[] =
  {
       0,     2,     2,     1,     7,     7,     7,     7,     7,     7,
       7,    11,    11,    11,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const declare::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "PARTICIPATION",
  "AT_MOST_ONE", "AT_MOST_TWO", "AT_MOST_THREE", "AT_LEAST_ONE", "INIT",
  "END", "RESPONDED_EXISTENCE", "RESPONSE", "ALTERNATED_RESPONSE",
  "CHAIN_RESPONSE", "PRECEDENCE", "ALTERNATED_PRECEDENCE",
  "CHAIN_PRECEDENCE", "CO_EXISTENCE", "SUCCESSION",
  "ALTERNATED_SUCCESSION", "CHAIN_SUCCESSION", "NOT_CHAIN_SUCCESSION",
  "NOT_SUCCESSION", "NOT_CO_EXISTENCE", "OP", "CL", "QUOTE", "COMMA",
  "EOL", "VAR", "$accept", "exp", "rule", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  declare::yyrline_[] =
  {
       0,    83,    83,    84,    89,    94,    99,   104,   109,   114,
     119,   126,   132,   138,   144,   150,   156,   162,   168,   174,
     180,   186,   192,   198,   204
  };

  void
  declare::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  declare::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  declare::symbol_kind_type
  declare::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
    };
    // Last valid token kind.
    const int code_max = 284;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

} // yy
#line 1281 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare-parser.cpp"

#line 210 "/Users/markmints/Developer/hibpm/src/hibpm/declare-parser/declare.yy"


// Main code in separated main.cpp file
