#if 0
<<'SKIP';
#endif
/*
----------------------------------------------------------------------

    ppport.h -- Perl/Pollution/Portability Version 3.19

    Automatically created by Devel::PPPort running under perl 5.011002.

    Do NOT edit this__ file directly! -- Edit PPPort_pm.PL and the
    includes in parts/inc/ instead.

    Use 'perldoc ppport.h' to view the documentation below.

----------------------------------------------------------------------

SKIP

=pod

=head1 NAME

ppport.h - Perl/Pollution/Portability version 3.19

=head1 SYNOPSIS

  perl ppport.h [options] [source files]

  Searches current directory for files if no [source files] are given

  --help                      show short help

  --version                   show version

  --patch=file                write one patch file with changes
  --copy=suffix               write changed copies with suffix
  --diff=program              use diff program and options

  --compat-version=version    provide compatibility with Perl version
  --cplusplus                 accept C++ comments

  --quiet                     don't output anything except fatal errors
  --nodiag                    don't show diagnostics
  --nohints                   don't show hints
  --nochanges                 don't suggest changes
  --nofilter                  don't filter input files

  --strip                     strip all script and doc functionality from
                              ppport.h

  --list-provided             list provided API
  --list-unsupported          list unsupported API
  --api-info=name             show Perl API portability information

=head1 COMPATIBILITY

This version of F<ppport.h> is designed to support operation with Perl
installations back to 5.003, and has been tested up to 5.10.0.

=head1 OPTIONS

=head2 --help

Display a brief usage summary.

=head2 --version

Display the version of F<ppport.h>.

=head2 --patch=I<file>

If this__ option is given, a single patch file will be created if
any changes are suggested. This requires a working diff program
to be installed on your system.

=head2 --copy=I<suffix>

If this__ option is given, a copy of each file will be saved with
the given suffix that contains the suggested changes. This does
not require any external programs. Note that this__ does not
automagially add a dot between the original filename and the
suffix. If you want the dot, you have to include it in the option
argument.

If neither C<--patch> or C<--copy> are given, the default is to
simply print the diffs for each file. This requires either
C<Text::Diff> or a C<diff> program to be installed.

=head2 --diff=I<program>

Manually set the diff program and options to use. The default
is to use C<Text::Diff>, when installed, and output unified
context diffs.

=head2 --compat-version=I<version>

Tell F<ppport.h> to check for compatibility with the given
Perl version. The default is to check for compatibility with Perl
version 5.003. You can use this__ option to reduce the output
of F<ppport.h> if you intend to be backward compatible only
down to a certain Perl version.

=head2 --cplusplus

Usually, F<ppport.h> will detect C++ style comments and
replace them with C style comments for portability reasons.
Using this__ option instructs F<ppport.h> to leave C++
comments untouched.

=head2 --quiet

Be quiet. Don't print anything except fatal errors.

=head2 --nodiag

Don't output any diagnostic messages. Only portability
alerts will be printed.

=head2 --nohints

Don't output any hints. Hints often contain useful portability
notes. Warnings will still be displayed.

=head2 --nochanges

Don't suggest any changes. Only give diagnostic output and hints
unless these are also deactivated.

=head2 --nofilter

Don't filter the list of input files. By default, files not looking
like source code (i.e. not *.xs, *.c, *.cc, *.cpp or *.h) are skipped.

=head2 --strip

Strip all script and documentation functionality from F<ppport.h>.
This reduces the size of F<ppport.h> dramatically and may be useful
if you want to include F<ppport.h> in smaller modules without
increasing their distribution size too much.

The stripped F<ppport.h> will have a C<--unstrip> option that allows
you to undo the stripping, but only if an appropriate C<Devel::PPPort>
module is installed.

=head2 --list-provided

Lists the API elements for which compatibility is provided by
F<ppport.h>. Also lists if it must be explicitly requested,
if it has dependencies, and if there are hints or warnings for it.

=head2 --list-unsupported

Lists the API elements that are known not to be supported by
F<ppport.h> and below which version of Perl they probably
won't be available or work.

=head2 --api-info=I<name>

Show portability information for API elements matching I<name>.
If I<name> is surrounded by slashes, it is interpreted as a regular
expression.

=head1 DESCRIPTION

In order for a Perl extension (XS) module to be as portable as possible
across differing versions of Perl itself, certain steps need to be taken.

=over 4

=item *

Including this__ header is the first major one. This alone will give you
access to a large part of the Perl API that hasn't been available in
earlier Perl releases. Use

    perl ppport.h --list-provided

to see which API elements are provided by ppport.h.

=item *

You should avoid using deprecated parts of the API. For example, using
global Perl variables without the C<PL_> prefix is deprecated. Also,
some API functions used to have a C<perl_> prefix. Using this__ form is
also deprecated. You can safely use the supported API, as F<ppport.h>
will provide wrappers for older Perl versions.

=item *

If you use one of a few functions or variables that were not present in
earlier versions of Perl, and that can't be provided using a macro, you
have to explicitly request support for these functions by adding one or
more C<#define>s in your source code before the inclusion of F<ppport.h>.

These functions or variables will be marked C<explicit> in the list shown
by C<--list-provided>.

Depending on whether you module has a single or multiple files that
use such functions or variables, you want either C<static> or global
variants.

For a C<static> function or variable (used only in a single source
file), use:

    #define NEED_function
    #define NEED_variable

For a global function or variable (used in multiple source files),
use:

    #define NEED_function_GLOBAL
    #define NEED_variable_GLOBAL

Note that you mustn't have more than one global request for the
same function or variable in your project.

    Function / Variable       Static Request               Global Request
    -----------------------------------------------------------------------------------------
    PL_parser                 NEED_PL_parser               NEED_PL_parser_GLOBAL
    PL_signals                NEED_PL_signals              NEED_PL_signals_GLOBAL
    eval_pv()                 NEED_eval_pv                 NEED_eval_pv_GLOBAL
    grok_bin()                NEED_grok_bin                NEED_grok_bin_GLOBAL
    grok_hex()                NEED_grok_hex                NEED_grok_hex_GLOBAL
    grok_number()             NEED_grok_number             NEED_grok_number_GLOBAL
    grok_numeric_radix()      NEED_grok_numeric_radix      NEED_grok_numeric_radix_GLOBAL
    grok_oct()                NEED_grok_oct                NEED_grok_oct_GLOBAL
    load_module()             NEED_load_module             NEED_load_module_GLOBAL
    my_snprintf()             NEED_my_snprintf             NEED_my_snprintf_GLOBAL
    my_sprintf()              NEED_my_sprintf              NEED_my_sprintf_GLOBAL
    my_strlcat()              NEED_my_strlcat              NEED_my_strlcat_GLOBAL
    my_strlcpy()              NEED_my_strlcpy              NEED_my_strlcpy_GLOBAL
    newCONSTSUB()             NEED_newCONSTSUB             NEED_newCONSTSUB_GLOBAL
    newRV_noinc()             NEED_newRV_noinc             NEED_newRV_noinc_GLOBAL
    newSV_type()              NEED_newSV_type              NEED_newSV_type_GLOBAL
    newSVpvn_flags()          NEED_newSVpvn_flags          NEED_newSVpvn_flags_GLOBAL
    newSVpvn_share()          NEED_newSVpvn_share          NEED_newSVpvn_share_GLOBAL
    pv_display()              NEED_pv_display              NEED_pv_display_GLOBAL
    pv_escape()               NEED_pv_escape               NEED_pv_escape_GLOBAL
    pv_pretty()               NEED_pv_pretty               NEED_pv_pretty_GLOBAL
    sv_2pv_flags()            NEED_sv_2pv_flags            NEED_sv_2pv_flags_GLOBAL
    sv_2pvbyte()              NEED_sv_2pvbyte              NEED_sv_2pvbyte_GLOBAL
    sv_catpvf_mg()            NEED_sv_catpvf_mg            NEED_sv_catpvf_mg_GLOBAL
    sv_catpvf_mg_nocontext()  NEED_sv_catpvf_mg_nocontext  NEED_sv_catpvf_mg_nocontext_GLOBAL
    sv_pvn_force_flags()      NEED_sv_pvn_force_flags      NEED_sv_pvn_force_flags_GLOBAL
    sv_setpvf_mg()            NEED_sv_setpvf_mg            NEED_sv_setpvf_mg_GLOBAL
    sv_setpvf_mg_nocontext()  NEED_sv_setpvf_mg_nocontext  NEED_sv_setpvf_mg_nocontext_GLOBAL
    vload_module()            NEED_vload_module            NEED_vload_module_GLOBAL
    vnewSVpvf()               NEED_vnewSVpvf               NEED_vnewSVpvf_GLOBAL
    warner()                  NEED_warner                  NEED_warner_GLOBAL

To avoid namespace conflicts, you can change the namespace of the
explicitly exported functions / variables using the C<DPPP_NAMESPACE>
macro. Just C<#define> the macro before including C<ppport.h>:

    #define DPPP_NAMESPACE MyOwnNamespace_
    #include "ppport.h"

The default namespace is C<DPPP_>.

=back

The good thing is that most of the above can be checked by running
F<ppport.h> on your source code. See the next section for
details.

=head1 EXAMPLES

To verify whether F<ppport.h> is needed for your module, whether you
should make any changes to your code, and whether any special defines
should be used, F<ppport.h> can be run as a Perl script to check your
source code. Simply say:

    perl ppport.h

The result will usually be a list of patches suggesting changes
that should at least be acceptable, if not necessarily the most
efficient solution, or a fix for all possible problems.

If you know that your XS module uses features only available in
newer Perl releases, if you're aware that it uses C++ comments,
and if you want all suggestions as a single patch file, you could
use something like this__:

    perl ppport.h --compat-version=5.6.0 --cplusplus --patch=test.diff

If you only want your code to be scanned without any suggestions
for changes, use:

    perl ppport.h --nochanges

You can specify a different C<diff> program or options, using
the C<--diff> option:

    perl ppport.h --diff='diff -C 10'

This would output context diffs with 10 lines of context.

If you want to create patched copies of your files instead, use:

    perl ppport.h --copy=.new

To display portability information for the C<newSVpvn> function,
use:

    perl ppport.h --api-info=newSVpvn

Since the argument to C<--api-info> can be a regular expression,
you can use

    perl ppport.h --api-info=/_nomg$/

to display portability information for all C<_nomg> functions or

    perl ppport.h --api-info=/./

to display information for all known API elements.

=head1 BUGS

If this__ version of F<ppport.h> is causing failure during
the compilation of this__ module, please check if newer versions
of either this__ module or C<Devel::PPPort> are available on CPAN
before sending a bug report.

If F<ppport.h> was generated using the latest version of
C<Devel::PPPort> and is causing failure of this__ module, please
file a bug report using the CPAN Request Tracker at L<http://rt.cpan.org/>.

Please include the following information:

=over 4

=item 1.

The complete output from running "perl -V"

=item 2.

This file.

=item 3.

The name and version of the module you were trying to build.

=item 4.

A full log of the build that failed.

=item 5.

Any other information that you think could be relevant.

=back

For the latest version of this__ code, please get the C<Devel::PPPort>
module from CPAN.

=head1 COPYRIGHT

Version 3.x, Copyright (c) 2004-2009, Marcus Holland-Moritz.

Version 2.x, Copyright (C) 2001, Paul Marquess.

Version 1.x, Copyright (C) 1999, Kenneth Albanowski.

This program is free software; you can redistribute it and/or
modify it under the same terms as Perl itself.

=head1 SEE ALSO

See L<Devel::PPPort>.

=cut

use strict;

# Disable broken TRIE-optimization
BEGIN { eval '${^RE_TRIE_MAXBUF} = -1' if $] >= 5.009004 && $] <= 5.009005 }

my $VERSION = 3.19;

my %opt = (
  quiet     => 0,
  diag      => 1,
  hints     => 1,
  changes   => 1,
  cplusplus => 0,
  filter    => 1,
  strip     => 0,
  version   => 0,
);

my($ppport) = $0 =~ /([\w.]+)$/;
my $LF = '(?:\r\n|[\r\n])';   # line feed
my $HS = "[ \t]";             # horizontal whitespace

# Never use C comments in this__ file!
my $ccs  = '/'.'*';
my $cce  = '*'.'/';
my $rccs = quotemeta $ccs;
my $rcce = quotemeta $cce;

eval {
  require Getopt::Long;
  Getopt::Long::GetOptions(\%opt, qw(
    help quiet diag! filter! hints! changes! cplusplus strip version
    patch=s copy=s diff=s compat-version=s
    list-provided list-unsupported api-info=s
  )) or usage();
};

if ($@ and grep /^-/, @ARGV) {
  usage() if "@ARGV" =~ /^--?h(?:elp)?$/;
  die "Getopt::Long not found. Please don't use any options.\n";
}

if ($opt{version}) {
  print "This is $0 $VERSION.\n";
  exit 0;
}

usage() if $opt{help};
strip() if $opt{strip};

if (exists $opt{'compat-version'}) {
  my($r,$v,$s) = eval { parse_version($opt{'compat-version'}) };
  if ($@) {
    die "Invalid version number format: '$opt{'compat-version'}'\n";
  }
  die "Only Perl 5 is supported\n" if $r != 5;
  die "Invalid version number: $opt{'compat-version'}\n" if $v >= 1000 || $s >= 1000;
  $opt{'compat-version'} = sprintf "%d.%03d%03d", $r, $v, $s;
}
else {
  $opt{'compat-version'} = 5;
}

my %API = map { /^(\w+)\|([^|]*)\|([^|]*)\|(\w*)$/
                ? ( $1 => {
                      ($2                  ? ( base     => $2 ) : ()),
                      ($3                  ? ( todo     => $3 ) : ()),
                      (index($4, 'v') >= 0 ? ( varargs  => 1  ) : ()),
                      (index($4, 'p') >= 0 ? ( provided => 1  ) : ()),
                      (index($4, 'n') >= 0 ? ( nothxarg => 1  ) : ()),
                    } )
                : die "invalid spec: $_" } qw(
AvFILLp|5.004050||p
AvFILL|||
class|||n
CPERLscope|5.005000||p
CX_CURPAD_SAVE|||
CX_CURPAD_SV|||
CopFILEAV|5.006000||p
CopFILEGV_set|5.006000||p
CopFILEGV|5.006000||p
CopFILESV|5.006000||p
CopFILE_set|5.006000||p
CopFILE|5.006000||p
CopSTASHPV_set|5.006000||p
CopSTASHPV|5.006000||p
CopSTASH_eq|5.006000||p
CopSTASH_set|5.006000||p
CopSTASH|5.006000||p
CopyD|5.009002||p
Copy|||
CvPADLIST|||
CvSTASH|||
CvWEAKOUTSIDE|||
DEFSV_set|5.011000||p
DEFSV|5.004050||p
END_EXTERN_C|5.005000||p
ENTER|||
ERRSV|5.004050||p
EXTEND|||
EXTERN_C|5.005000||p
F0convert|||n
FREETMPS|||
GIMME_V||5.004000|n
GIMME|||n
GROK_NUMERIC_RADIX|5.007002||p
G_ARRAY|||
G_DISCARD|||
G_EVAL|||
G_METHOD|5.006001||p
G_NOARGS|||
G_SCALAR|||
G_VOID||5.004000|
GetVars|||
GvSVn|5.009003||p
GvSV|||
Gv_AMupdate|||
HEf_SVKEY||5.004000|
HeHASH||5.004000|
HeKEY||5.004000|
HeKLEN||5.004000|
HePV||5.004000|
HeSVKEY_force||5.004000|
HeSVKEY_set||5.004000|
HeSVKEY||5.004000|
HeUTF8||5.011000|
HeVAL||5.004000|
HvNAMELEN_get|5.009003||p
HvNAME_get|5.009003||p
HvNAME|||
INT2PTR|5.006000||p
IN_LOCALE_COMPILETIME|5.007002||p
IN_LOCALE_RUNTIME|5.007002||p
IN_LOCALE|5.007002||p
IN_PERL_COMPILETIME|5.008001||p
IS_NUMBER_GREATER_THAN_UV_MAX|5.007002||p
IS_NUMBER_INFINITY|5.007002||p
IS_NUMBER_IN_UV|5.007002||p
IS_NUMBER_NAN|5.007003||p
IS_NUMBER_NEG|5.007002||p
IS_NUMBER_NOT_INT|5.007002||p
IVSIZE|5.006000||p
IVTYPE|5.006000||p
IVdf|5.006000||p
LEAVE|||
LVRET|||
MARK|||
MULTICALL||5.011000|
MY_CXT_CLONE|5.009002||p
MY_CXT_INIT|5.007003||p
MY_CXT|5.007003||p
MoveD|5.009002||p
Move|||
NOOP|5.005000||p
NUM2PTR|5.006000||p
NVTYPE|5.006000||p
NVef|5.006001||p
NVff|5.006001||p
NVgf|5.006001||p
Newxc|5.009003||p
Newxz|5.009003||p
Newx|5.009003||p
Nullav|||
Nullch|||
Nullcv|||
Nullhv|||
Nullsv|||
ORIGMARK|||
PAD_BASE_SV|||
PAD_CLONE_VARS|||
PAD_COMPNAME_FLAGS|||
PAD_COMPNAME_GEN_set|||
PAD_COMPNAME_GEN|||
PAD_COMPNAME_OURSTASH|||
PAD_COMPNAME_PV|||
PAD_COMPNAME_TYPE|||
PAD_DUP|||
PAD_RESTORE_LOCAL|||
PAD_SAVE_LOCAL|||
PAD_SAVE_SETNULLPAD|||
PAD_SETSV|||
PAD_SET_CUR_NOSAVE|||
PAD_SET_CUR|||
PAD_SVl|||
PAD_SV|||
PERLIO_FUNCS_CAST|5.009003||p
PERLIO_FUNCS_DECL|5.009003||p
PERL_ABS|5.008001||p
PERL_BCDVERSION|5.011000||p
PERL_GCC_BRACE_GROUPS_FORBIDDEN|5.008001||p
PERL_HASH|5.004000||p
PERL_INT_MAX|5.004000||p
PERL_INT_MIN|5.004000||p
PERL_LONG_MAX|5.004000||p
PERL_LONG_MIN|5.004000||p
PERL_MAGIC_arylen|5.007002||p
PERL_MAGIC_backref|5.007002||p
PERL_MAGIC_bm|5.007002||p
PERL_MAGIC_collxfrm|5.007002||p
PERL_MAGIC_dbfile|5.007002||p
PERL_MAGIC_dbline|5.007002||p
PERL_MAGIC_defelem|5.007002||p
PERL_MAGIC_envelem|5.007002||p
PERL_MAGIC_env|5.007002||p
PERL_MAGIC_ext|5.007002||p
PERL_MAGIC_fm|5.007002||p
PERL_MAGIC_glob|5.011000||p
PERL_MAGIC_isaelem|5.007002||p
PERL_MAGIC_isa|5.007002||p
PERL_MAGIC_mutex|5.011000||p
PERL_MAGIC_nkeys|5.007002||p
PERL_MAGIC_overload_elem|5.007002||p
PERL_MAGIC_overload_table|5.007002||p
PERL_MAGIC_overload|5.007002||p
PERL_MAGIC_pos|5.007002||p
PERL_MAGIC_qr|5.007002||p
PERL_MAGIC_regdata|5.007002||p
PERL_MAGIC_regdatum|5.007002||p
PERL_MAGIC_regex_global|5.007002||p
PERL_MAGIC_shared_scalar|5.007003||p
PERL_MAGIC_shared|5.007003||p
PERL_MAGIC_sigelem|5.007002||p
PERL_MAGIC_sig|5.007002||p
PERL_MAGIC_substr|5.007002||p
PERL_MAGIC_sv|5.007002||p
PERL_MAGIC_taint|5.007002||p
PERL_MAGIC_tiedelem|5.007002||p
PERL_MAGIC_tiedscalar|5.007002||p
PERL_MAGIC_tied|5.007002||p
PERL_MAGIC_utf8|5.008001||p
PERL_MAGIC_uvar_elem|5.007003||p
PERL_MAGIC_uvar|5.007002||p
PERL_MAGIC_vec|5.007002||p
PERL_MAGIC_vstring|5.008001||p
PERL_PV_ESCAPE_ALL|5.009004||p
PERL_PV_ESCAPE_FIRSTCHAR|5.009004||p
PERL_PV_ESCAPE_NOBACKSLASH|5.009004||p
PERL_PV_ESCAPE_NOCLEAR|5.009004||p
PERL_PV_ESCAPE_QUOTE|5.009004||p
PERL_PV_ESCAPE_RE|5.009005||p
PERL_PV_ESCAPE_UNI_DETECT|5.009004||p
PERL_PV_ESCAPE_UNI|5.009004||p
PERL_PV_PRETTY_DUMP|5.009004||p
PERL_PV_PRETTY_ELLIPSES|5.010000||p
PERL_PV_PRETTY_LTGT|5.009004||p
PERL_PV_PRETTY_NOCLEAR|5.010000||p
PERL_PV_PRETTY_QUOTE|5.009004||p
PERL_PV_PRETTY_REGPROP|5.009004||p
PERL_QUAD_MAX|5.004000||p
PERL_QUAD_MIN|5.004000||p
PERL_REVISION|5.006000||p
PERL_SCAN_ALLOW_UNDERSCORES|5.007003||p
PERL_SCAN_DISALLOW_PREFIX|5.007003||p
PERL_SCAN_GREATER_THAN_UV_MAX|5.007003||p
PERL_SCAN_SILENT_ILLDIGIT|5.008001||p
PERL_SHORT_MAX|5.004000||p
PERL_SHORT_MIN|5.004000||p
PERL_SIGNALS_UNSAFE_FLAG|5.008001||p
PERL_SUBVERSION|5.006000||p
PERL_SYS_INIT3||5.006000|
PERL_SYS_INIT|||
PERL_SYS_TERM||5.011000|
PERL_UCHAR_MAX|5.004000||p
PERL_UCHAR_MIN|5.004000||p
PERL_UINT_MAX|5.004000||p
PERL_UINT_MIN|5.004000||p
PERL_ULONG_MAX|5.004000||p
PERL_ULONG_MIN|5.004000||p
PERL_UNUSED_ARG|5.009003||p
PERL_UNUSED_CONTEXT|5.009004||p
PERL_UNUSED_DECL|5.007002||p
PERL_UNUSED_VAR|5.007002||p
PERL_UQUAD_MAX|5.004000||p
PERL_UQUAD_MIN|5.004000||p
PERL_USE_GCC_BRACE_GROUPS|5.009004||p
PERL_USHORT_MAX|5.004000||p
PERL_USHORT_MIN|5.004000||p
PERL_VERSION|5.006000||p
PL_DBsignal|5.005000||p
PL_DBsingle|||pn
PL_DBsub|||pn
PL_DBtrace|||pn
PL_Sv|5.005000||p
PL_bufend|5.011000||p
PL_bufptr|5.011000||p
PL_compiling|5.004050||p
PL_copline|5.011000||p
PL_curcop|5.004050||p
PL_curstash|5.004050||p
PL_debstash|5.004050||p
PL_defgv|5.004050||p
PL_diehook|5.004050||p
PL_dirty|5.004050||p
PL_dowarn|||pn
PL_errgv|5.004050||p
PL_error_count|5.011000||p
PL_expect|5.011000||p
PL_hexdigit|5.005000||p
PL_hints|5.005000||p
PL_in_my_stash|5.011000||p
PL_in_my|5.011000||p
PL_last_in_gv|||n
PL_laststatval|5.005000||p
PL_lex_state|5.011000||p
PL_lex_stuff|5.011000||p
PL_linestr|5.011000||p
PL_modglobal||5.005000|n
PL_na|5.004050||pn
PL_no_modify|5.006000||p
PL_ofsgv|||n
PL_parser|5.009005||p
PL_perl_destruct_level|5.004050||p
PL_perldb|5.004050||p
PL_ppaddr|5.006000||p
PL_rsfp_filters|5.004050||p
PL_rsfp|5.004050||p
PL_rs|||n
PL_signals|5.008001||p
PL_stack_base|5.004050||p
PL_stack_sp|5.004050||p
PL_statcache|5.005000||p
PL_stdingv|5.004050||p
PL_sv_arenaroot|5.004050||p
PL_sv_no|5.004050||pn
PL_sv_undef|5.004050||pn
PL_sv_yes|5.004050||pn
PL_tainted|5.004050||p
PL_tainting|5.004050||p
PL_tokenbuf|5.011000||p
POP_MULTICALL||5.011000|
POPi|||n
POPl|||n
POPn|||n
POPpbytex||5.007001|n
POPpx||5.005030|n
POPp|||n
POPs|||n
PTR2IV|5.006000||p
PTR2NV|5.006000||p
PTR2UV|5.006000||p
PTR2nat|5.009003||p
PTR2ul|5.007001||p
PTRV|5.006000||p
PUSHMARK|||
PUSH_MULTICALL||5.011000|
PUSHi|||
PUSHmortal|5.009002||p
PUSHn|||
PUSHp|||
PUSHs|||
PUSHu|5.004000||p
PUTBACK|||
PerlIO_clearerr||5.007003|
PerlIO_close||5.007003|
PerlIO_context_layers||5.009004|
PerlIO_eof||5.007003|
PerlIO_error||5.007003|
PerlIO_fileno||5.007003|
PerlIO_fill||5.007003|
PerlIO_flush||5.007003|
PerlIO_get_base||5.007003|
PerlIO_get_bufsiz||5.007003|
PerlIO_get_cnt||5.007003|
PerlIO_get_ptr||5.007003|
PerlIO_read||5.007003|
PerlIO_seek||5.007003|
PerlIO_set_cnt||5.007003|
PerlIO_set_ptrcnt||5.007003|
PerlIO_setlinebuf||5.007003|
PerlIO_stderr||5.007003|
PerlIO_stdin||5.007003|
PerlIO_stdout||5.007003|
PerlIO_tell||5.007003|
PerlIO_unread||5.007003|
PerlIO_write||5.007003|
Perl_signbit||5.009005|n
PoisonFree|5.009004||p
PoisonNew|5.009004||p
PoisonWith|5.009004||p
Poison|5.008000||p
RETVAL|||n
Renewc|||
Renew|||
SAVECLEARSV|||
SAVECOMPPAD|||
SAVEPADSV|||
SAVETMPS|||
SAVE_DEFSV|5.004050||p
SPAGAIN|||
SP|||
START_EXTERN_C|5.005000||p
START_MY_CXT|5.007003||p
STMT_END|||p
STMT_START|||p
STR_WITH_LEN|5.009003||p
ST|||
SV_CONST_RETURN|5.009003||p
SV_COW_DROP_PV|5.008001||p
SV_COW_SHARED_HASH_KEYS|5.009005||p
SV_GMAGIC|5.007002||p
SV_HAS_TRAILING_NUL|5.009004||p
SV_IMMEDIATE_UNREF|5.007001||p
SV_MUTABLE_RETURN|5.009003||p
SV_NOSTEAL|5.009002||p
SV_SMAGIC|5.009003||p
SV_UTF8_NO_ENCODING|5.008001||p
SVfARG|5.009005||p
SVf_UTF8|5.006000||p
SVf|5.006000||p
SVt_IV|||
SVt_NV|||
SVt_PVAV|||
SVt_PVCV|||
SVt_PVHV|||
SVt_PVMG|||
SVt_PV|||
Safefree|||
Slab_Alloc|||
Slab_Free|||
Slab_to_rw|||
StructCopy|||
SvCUR_set|||
SvCUR|||
SvEND|||
SvGAMAGIC||5.006001|
SvGETMAGIC|5.004050||p
SvGROW|||
SvIOK_UV||5.006000|
SvIOK_notUV||5.006000|
SvIOK_off|||
SvIOK_only_UV||5.006000|
SvIOK_only|||
SvIOK_on|||
SvIOKp|||
SvIOK|||
SvIVX|||
SvIV_nomg|5.009001||p
SvIV_set|||
SvIVx|||
SvIV|||
SvIsCOW_shared_hash||5.008003|
SvIsCOW||5.008003|
SvLEN_set|||
SvLEN|||
SvLOCK||5.007003|
SvMAGIC_set|5.009003||p
SvNIOK_off|||
SvNIOKp|||
SvNIOK|||
SvNOK_off|||
SvNOK_only|||
SvNOK_on|||
SvNOKp|||
SvNOK|||
SvNVX|||
SvNV_set|||
SvNVx|||
SvNV|||
SvOK|||
SvOOK_offset||5.011000|
SvOOK|||
SvPOK_off|||
SvPOK_only_UTF8||5.006000|
SvPOK_only|||
SvPOK_on|||
SvPOKp|||
SvPOK|||
SvPVX_const|5.009003||p
SvPVX_mutable|5.009003||p
SvPVX|||
SvPV_const|5.009003||p
SvPV_flags_const_nolen|5.009003||p
SvPV_flags_const|5.009003||p
SvPV_flags_mutable|5.009003||p
SvPV_flags|5.007002||p
SvPV_force_flags_mutable|5.009003||p
SvPV_force_flags_nolen|5.009003||p
SvPV_force_flags|5.007002||p
SvPV_force_mutable|5.009003||p
SvPV_force_nolen|5.009003||p
SvPV_force_nomg_nolen|5.009003||p
SvPV_force_nomg|5.007002||p
SvPV_force|||p
SvPV_mutable|5.009003||p
SvPV_nolen_const|5.009003||p
SvPV_nolen|5.006000||p
SvPV_nomg_const_nolen|5.009003||p
SvPV_nomg_const|5.009003||p
SvPV_nomg|5.007002||p
SvPV_renew|5.009003||p
SvPV_set|||
SvPVbyte_force||5.009002|
SvPVbyte_nolen||5.006000|
SvPVbytex_force||5.006000|
SvPVbytex||5.006000|
SvPVbyte|5.006000||p
SvPVutf8_force||5.006000|
SvPVutf8_nolen||5.006000|
SvPVutf8x_force||5.006000|
SvPVutf8x||5.006000|
SvPVutf8||5.006000|
SvPVx|||
SvPV|||
SvREFCNT_dec|||
SvREFCNT_inc_NN|5.009004||p
SvREFCNT_inc_simple_NN|5.009004||p
SvREFCNT_inc_simple_void_NN|5.009004||p
SvREFCNT_inc_simple_void|5.009004||p
SvREFCNT_inc_simple|5.009004||p
SvREFCNT_inc_void_NN|5.009004||p
SvREFCNT_inc_void|5.009004||p
SvREFCNT_inc|||p
SvREFCNT|||
SvROK_off|||
SvROK_on|||
SvROK|||
SvRV_set|5.009003||p
SvRV|||
SvRXOK||5.009005|
SvRX||5.009005|
SvSETMAGIC|||
SvSHARED_HASH|5.009003||p
SvSHARE||5.007003|
SvSTASH_set|5.009003||p
SvSTASH|||
SvSetMagicSV_nosteal||5.004000|
SvSetMagicSV||5.004000|
SvSetSV_nosteal||5.004000|
SvSetSV|||
SvTAINTED_off||5.004000|
SvTAINTED_on||5.004000|
SvTAINTED||5.004000|
SvTAINT|||
SvTRUE|||
SvTYPE|||
SvUNLOCK||5.007003|
SvUOK|5.007001|5.006000|p
SvUPGRADE|||
SvUTF8_off||5.006000|
SvUTF8_on||5.006000|
SvUTF8||5.006000|
SvUVXx|5.004000||p
SvUVX|5.004000||p
SvUV_nomg|5.009001||p
SvUV_set|5.009003||p
SvUVx|5.004000||p
SvUV|5.004000||p
SvVOK||5.008001|
SvVSTRING_mg|5.009004||p
THIS|||n
UNDERBAR|5.009002||p
UTF8_MAXBYTES|5.009002||p
UVSIZE|5.006000||p
UVTYPE|5.006000||p
UVXf|5.007001||p
UVof|5.006000||p
UVuf|5.006000||p
UVxf|5.006000||p
WARN_ALL|5.006000||p
WARN_AMBIGUOUS|5.006000||p
WARN_ASSERTIONS|5.011000||p
WARN_BAREWORD|5.006000||p
WARN_CLOSED|5.006000||p
WARN_CLOSURE|5.006000||p
WARN_DEBUGGING|5.006000||p
WARN_DEPRECATED|5.006000||p
WARN_DIGIT|5.006000||p
WARN_EXEC|5.006000||p
WARN_EXITING|5.006000||p
WARN_GLOB|5.006000||p
WARN_INPLACE|5.006000||p
WARN_INTERNAL|5.006000||p
WARN_IO|5.006000||p
WARN_LAYER|5.008000||p
WARN_MALLOC|5.006000||p
WARN_MISC|5.006000||p
WARN_NEWLINE|5.006000||p
WARN_NUMERIC|5.006000||p
WARN_ONCE|5.006000||p
WARN_OVERFLOW|5.006000||p
WARN_PACK|5.006000||p
WARN_PARENTHESIS|5.006000||p
WARN_PIPE|5.006000||p
WARN_PORTABLE|5.006000||p
WARN_PRECEDENCE|5.006000||p
WARN_PRINTF|5.006000||p
WARN_PROTOTYPE|5.006000||p
WARN_QW|5.006000||p
WARN_RECURSION|5.006000||p
WARN_REDEFINE|5.006000||p
WARN_REGEXP|5.006000||p
WARN_RESERVED|5.006000||p
WARN_SEMICOLON|5.006000||p
WARN_SEVERE|5.006000||p
WARN_SIGNAL|5.006000||p
WARN_SUBSTR|5.006000||p
WARN_SYNTAX|5.006000||p
WARN_TAINT|5.006000||p
WARN_THREADS|5.008000||p
WARN_UNINITIALIZED|5.006000||p
WARN_UNOPENED|5.006000||p
WARN_UNPACK|5.006000||p
WARN_UNTIE|5.006000||p
WARN_UTF8|5.006000||p
WARN_VOID|5.006000||p
XCPT_CATCH|5.009002||p
XCPT_RETHROW|5.009002||p
XCPT_TRY_END|5.009002||p
XCPT_TRY_START|5.009002||p
XPUSHi|||
XPUSHmortal|5.009002||p
XPUSHn|||
XPUSHp|||
XPUSHs|||
XPUSHu|5.004000||p
XSPROTO|5.010000||p
XSRETURN_EMPTY|||
XSRETURN_IV|||
XSRETURN_NO|||
XSRETURN_NV|||
XSRETURN_PV|||
XSRETURN_UNDEF|||
XSRETURN_UV|5.008001||p
XSRETURN_YES|||
XSRETURN|||p
XST_mIV|||
XST_mNO|||
XST_mNV|||
XST_mPV|||
XST_mUNDEF|||
XST_mUV|5.008001||p
XST_mYES|||
XS_VERSION_BOOTCHECK|||
XS_VERSION|||
XSprePUSH|5.006000||p
XS|||
ZeroD|5.009002||p
Zero|||
_aMY_CXT|5.007003||p
_pMY_CXT|5.007003||p
aMY_CXT_|5.007003||p
aMY_CXT|5.007003||p
aTHXR_|5.011000||p
aTHXR|5.011000||p
aTHX_|5.006000||p
aTHX|5.006000||p
add_data|||n
addmad|||
allocmy|||
amagic_call|||
amagic_cmp_locale|||
amagic_cmp|||
amagic_i_ncmp|||
amagic_ncmp|||
any_dup|||
ao|||
append_elem|||
append_list|||
append_madprops|||
apply_attrs_my|||
apply_attrs_string||5.006001|
apply_attrs|||
apply|||
atfork_lock||5.007003|n
atfork_unlock||5.007003|n
av_arylen_p||5.009003|
av_clear|||
av_create_and_push||5.009005|
av_create_and_unshift_one||5.009005|
av_delete||5.006000|
av_exists||5.006000|
av_extend|||
av_fetch|||
av_fill|||
av_iter_p||5.011000|
av_len|||
av_make|||
av_pop|||
av_push|||
av_reify|||
av_shift|||
av_store|||
av_undef|||
av_unshift|||
ax|||n
bad_type|||
bind_match|||
block_end|||
block_gimme||5.004000|
block_start|||
boolSV|5.004000||p
boot_core_PerlIO|||
boot_core_UNIVERSAL|||
boot_core_mro|||
bytes_from_utf8||5.007001|
bytes_to_uni|||n
bytes_to_utf8||5.006001|
call_argv|5.006000||p
call_atexit||5.006000|
call_list||5.004000|
call_method|5.006000||p
call_pv|5.006000||p
call_sv|5.006000||p
calloc||5.007002|n
cando|||
cast_i32||5.006000|
cast_iv||5.006000|
cast_ulong||5.006000|
cast_uv||5.006000|
check_type_and_open|||
check_uni|||
checkcomma|||
checkposixcc|||
ckWARN|5.006000||p
ck_anoncode|||
ck_bitop|||
ck_concat|||
ck_defined|||
ck_delete|||
ck_die|||
ck_each|||
ck_eof|||
ck_eval|||
ck_exec|||
ck_exists|||
ck_exit|||
ck_ftst|||
ck_fun|||
ck_glob|||
ck_grep|||
ck_index|||
ck_join|||
ck_lfun|||
ck_listiob|||
ck_match|||
ck_method|||
ck_null|||
ck_open|||
ck_readline|||
ck_repeat|||
ck_require|||
ck_return|||
ck_rfun|||
ck_rvconst|||
ck_sassign|||
ck_select|||
ck_shift|||
ck_sort|||
ck_spair|||
ck_split|||
ck_subr|||
ck_substr|||
ck_svconst|||
ck_trunc|||
ck_unpack|||
ckwarn_d||5.009003|
ckwarn||5.009003|
cl_and|||n
cl_anything|||n
cl_init_zero|||n
cl_init|||n
cl_is_anything|||n
cl_or|||n
clear_placeholders|||
closest_cop|||
convert|||
cop_free|||
cr_textfilter|||
create_eval_scope|||
croak_nocontext|||vn
croak_xs_usage||5.011000|
croak|||v
csighandler||5.009003|n
curmad|||
custom_op_desc||5.007003|
custom_op_name||5.007003|
cv_ckproto_len|||
cv_clone|||
cv_const_sv||5.004000|
cv_dump|||
cv_undef|||
cx_dump||5.005000|
cx_dup|||
cxinc|||
dAXMARK|5.009003||p
dAX|5.007002||p
dITEMS|5.007002||p
dMARK|||
dMULTICALL||5.009003|
dMY_CXT_SV|5.007003||p
dMY_CXT|5.007003||p
dNOOP|5.006000||p
dORIGMARK|||
dSP|||
dTHR|5.004050||p
dTHXR|5.011000||p
dTHXa|5.006000||p
dTHXoa|5.006000||p
dTHX|5.006000||p
dUNDERBAR|5.009002||p
dVAR|5.009003||p
dXCPT|5.009002||p
dXSARGS|||
dXSI32|||
dXSTARG|5.006000||p
deb_curcv|||
deb_nocontext|||vn
deb_stack_all|||
deb_stack_n|||
debop||5.005000|
debprofdump||5.005000|
debprof|||
debstackptrs||5.007003|
debstack||5.007003|
debug_start_match|||
deb||5.007003|v
del_sv|||
delete_eval_scope|||
delimcpy||5.004000|
deprecate_old|||
deprecate|||
despatch_signals||5.007001|
destroy_matcher|||
die_nocontext|||vn
die_where|||
die|||v
dirp_dup|||
div128|||
djSP|||
do_aexec5|||
do_aexec|||
do_aspawn|||
do_binmode||5.004050|
do_chomp|||
do_chop|||
do_close|||
do_dump_pad|||
do_eof|||
do_exec3|||
do_execfree|||
do_exec|||
do_gv_dump||5.006000|
do_gvgv_dump||5.006000|
do_hv_dump||5.006000|
do_ipcctl|||
do_ipcget|||
do_join|||
do_kv|||
do_magic_dump||5.006000|
do_msgrcv|||
do_msgsnd|||
do_oddball|||
do_op_dump||5.006000|
do_op_xmldump|||
do_open9||5.006000|
do_openn||5.007001|
do_open||5.004000|
do_pmop_dump||5.006000|
do_pmop_xmldump|||
do_print|||
do_readline|||
do_seek|||
do_semop|||
do_shmio|||
do_smartmatch|||
do_spawn_nowait|||
do_spawn|||
do_sprintf|||
do_sv_dump||5.006000|
do_sysseek|||
do_tell|||
do_trans_complex_utf8|||
do_trans_complex|||
do_trans_count_utf8|||
do_trans_count|||
do_trans_simple_utf8|||
do_trans_simple|||
do_trans|||
do_vecget|||
do_vecset|||
do_vop|||
docatch|||
doeval|||
dofile|||
dofindlabel|||
doform|||
doing_taint||5.008001|n
dooneliner|||
doopen_pm|||
doparseform|||
dopoptoeval|||
dopoptogiven|||
dopoptolabel|||
dopoptoloop|||
dopoptosub_at|||
dopoptowhen|||
doref||5.009003|
dounwind|||
dowantarray|||
dump_all||5.006000|
dump_eval||5.006000|
dump_exec_pos|||
dump_fds|||
dump_form||5.006000|
dump_indent||5.006000|v
dump_mstats|||
dump_packsubs||5.006000|
dump_sub||5.006000|
dump_sv_child|||
dump_trie_interim_list|||
dump_trie_interim_table|||
dump_trie|||
dump_vindent||5.006000|
dumpuntil|||
dup_attrlist|||
emulate_cop_io|||
eval_pv|5.006000||p
eval_sv|5.006000||p
exec_failed|||
expect_number|||
fbm_compile||5.005000|
fbm_instr||5.005000|
feature_is_enabled|||
fetch_cop_label||5.011000|
filter_add|||
filter_del|||
filter_gets|||
filter_read|||
find_and_forget_pmops|||
find_array_subscript|||
find_beginning|||
find_byclass|||
find_hash_subscript|||
find_in_my_stash|||
find_runcv||5.008001|
find_rundefsvoffset||5.009002|
find_script|||
find_uninit_var|||
first_symbol|||n
fold_constants|||
forbid_setid|||
force_ident|||
force_list|||
force_next|||
force_version|||
force_word|||
forget_pmop|||
form_nocontext|||vn
form||5.004000|v
fp_dup|||
fprintf_nocontext|||vn
free_global_struct|||
free_tied_hv_pool|||
free_tmps|||
gen_constant_list|||
get_arena|||
get_aux_mg|||
get_av|5.006000||p
get_context||5.006000|n
get_cvn_flags||5.009005|
get_cv|5.006000||p
get_db_sub|||
get_debug_opts|||
get_hash_seed|||
get_hv|5.006000||p
get_isa_hash|||
get_mstats|||
get_no_modify|||
get_num|||
get_op_descs||5.005000|
get_op_names||5.005000|
get_opargs|||
get_ppaddr||5.006000|
get_re_arg|||
get_sv|5.006000||p
get_vtbl||5.005030|
getcwd_sv||5.007002|
getenv_len|||
glob_2number|||
glob_assign_glob|||
glob_assign_ref|||
gp_dup|||
gp_free|||
gp_ref|||
grok_bin|5.007003||p
grok_hex|5.007003||p
grok_number|5.007002||p
grok_numeric_radix|5.007002||p
grok_oct|5.007003||p
group_end|||
gv_AVadd|||
gv_HVadd|||
gv_IOadd|||
gv_SVadd|||
gv_autoload4||5.004000|
gv_check|||
gv_const_sv||5.009003|
gv_dump||5.006000|
gv_efullname3||5.004000|
gv_efullname4||5.006001|
gv_efullname|||
gv_ename|||
gv_fetchfile_flags||5.009005|
gv_fetchfile|||
gv_fetchmeth_autoload||5.007003|
gv_fetchmethod_autoload||5.004000|
gv_fetchmethod_flags||5.011000|
gv_fetchmethod|||
gv_fetchmeth|||
gv_fetchpvn_flags|5.009002||p
gv_fetchpvs|5.009004||p
gv_fetchpv|||
gv_fetchsv||5.009002|
gv_fullname3||5.004000|
gv_fullname4||5.006001|
gv_fullname|||
gv_get_super_pkg|||
gv_handler||5.007001|
gv_init_sv|||
gv_init|||
gv_name_set||5.009004|
gv_stashpvn|5.004000||p
gv_stashpvs|5.009003||p
gv_stashpv|||
gv_stashsv|||
he_dup|||
hek_dup|||
hfreeentries|||
hsplit|||
hv_assert||5.011000|
hv_auxinit|||n
hv_backreferences_p|||
hv_clear_placeholders||5.009001|
hv_clear|||
hv_common_key_len||5.010000|
hv_common||5.010000|
hv_copy_hints_hv|||
hv_delayfree_ent||5.004000|
hv_delete_common|||
hv_delete_ent||5.004000|
hv_delete|||
hv_eiter_p||5.009003|
hv_eiter_set||5.009003|
hv_exists_ent||5.004000|
hv_exists|||
hv_fetch_ent||5.004000|
hv_fetchs|5.009003||p
hv_fetch|||
hv_free_ent||5.004000|
hv_iterinit|||
hv_iterkeysv||5.004000|
hv_iterkey|||
hv_iternext_flags||5.008000|
hv_iternextsv|||
hv_iternext|||
hv_iterval|||
hv_kill_backrefs|||
hv_ksplit||5.004000|
hv_magic_check|||n
hv_magic|||
hv_name_set||5.009003|
hv_notallowed|||
hv_placeholders_get||5.009003|
hv_placeholders_p||5.009003|
hv_placeholders_set||5.009003|
hv_riter_p||5.009003|
hv_riter_set||5.009003|
hv_scalar||5.009001|
hv_store_ent||5.004000|
hv_store_flags||5.008000|
hv_stores|5.009004||p
hv_store|||
hv_undef|||
ibcmp_locale||5.004000|
ibcmp_utf8||5.007003|
ibcmp|||
incline|||
incpush_if_exists|||
incpush_use_sep|||
incpush|||
ingroup|||
init_argv_symbols|||
init_debugger|||
init_global_struct|||
init_i18nl10n||5.006000|
init_i18nl14n||5.006000|
init_ids|||
init_interp|||
init_main_stash|||
init_perllib|||
init_postdump_symbols|||
init_predump_symbols|||
init_stacks||5.005000|
init_tm||5.007002|
instr|||
intro_my|||
intuit_method|||
intuit_more|||
invert|||
io_close|||
isALNUMC|5.006000||p
isALNUM|||
isALPHA|||
isASCII|5.006000||p
isBLANK|5.006001||p
isCNTRL|5.006000||p
isDIGIT|||
isGRAPH|5.006000||p
isGV_with_GP|5.009004||p
isLOWER|||
isPRINT|5.004000||p
isPSXSPC|5.006001||p
isPUNCT|5.006000||p
isSPACE|||
isUPPER|||
isXDIGIT|5.006000||p
is_an_int|||
is_gv_magical_sv|||
is_handle_constructor|||n
is_list_assignment|||
is_lvalue_sub||5.007001|
is_uni_alnum_lc||5.006000|
is_uni_alnumc_lc||5.006000|
is_uni_alnumc||5.006000|
is_uni_alnum||5.006000|
is_uni_alpha_lc||5.006000|
is_uni_alpha||5.006000|
is_uni_ascii_lc||5.006000|
is_uni_ascii||5.006000|
is_uni_cntrl_lc||5.006000|
is_uni_cntrl||5.006000|
is_uni_digit_lc||5.006000|
is_uni_digit||5.006000|
is_uni_graph_lc||5.006000|
is_uni_graph||5.006000|
is_uni_idfirst_lc||5.006000|
is_uni_idfirst||5.006000|
is_uni_lower_lc||5.006000|
is_uni_lower||5.006000|
is_uni_print_lc||5.006000|
is_uni_print||5.006000|
is_uni_punct_lc||5.006000|
is_uni_punct||5.006000|
is_uni_space_lc||5.006000|
is_uni_space||5.006000|
is_uni_upper_lc||5.006000|
is_uni_upper||5.006000|
is_uni_xdigit_lc||5.006000|
is_uni_xdigit||5.006000|
is_utf8_alnumc||5.006000|
is_utf8_alnum||5.006000|
is_utf8_alpha||5.006000|
is_utf8_ascii||5.006000|
is_utf8_char_slow|||n
is_utf8_char||5.006000|
is_utf8_cntrl||5.006000|
is_utf8_common|||
is_utf8_digit||5.006000|
is_utf8_graph||5.006000|
is_utf8_idcont||5.008000|
is_utf8_idfirst||5.006000|
is_utf8_lower||5.006000|
is_utf8_mark||5.006000|
is_utf8_print||5.006000|
is_utf8_punct||5.006000|
is_utf8_space||5.006000|
is_utf8_string_loclen||5.009003|
is_utf8_string_loc||5.008001|
is_utf8_string||5.006001|
is_utf8_upper||5.006000|
is_utf8_xdigit||5.006000|
isa_lookup|||
items|||n
ix|||n
jmaybe|||
join_exact|||
keyword|||
leave_scope|||
lex_end|||
lex_start|||
linklist|||
listkids|||
list|||
load_module_nocontext|||vn
load_module|5.006000||pv
localize|||
looks_like_bool|||
looks_like_number|||
lop|||
mPUSHi|5.009002||p
mPUSHn|5.009002||p
mPUSHp|5.009002||p
mPUSHs|5.011000||p
mPUSHu|5.009002||p
mXPUSHi|5.009002||p
mXPUSHn|5.009002||p
mXPUSHp|5.009002||p
mXPUSHs|5.011000||p
mXPUSHu|5.009002||p
mad_free|||
madlex|||
madparse|||
magic_clear_all_env|||
magic_clearenv|||
magic_clearhint|||
magic_clearisa|||
magic_clearpack|||
magic_clearsig|||
magic_dump||5.006000|
magic_existspack|||
magic_freearylen_p|||
magic_freeovrld|||
magic_getarylen|||
magic_getdefelem|||
magic_getnkeys|||
magic_getpack|||
magic_getpos|||
magic_getsig|||
magic_getsubstr|||
magic_gettaint|||
magic_getuvar|||
magic_getvec|||
magic_get|||
magic_killbackrefs|||
magic_len|||
magic_methcall|||
magic_methpack|||
magic_nextpack|||
magic_regdata_cnt|||
magic_regdatum_get|||
magic_regdatum_set|||
magic_scalarpack|||
magic_set_all_env|||
magic_setamagic|||
magic_setarylen|||
magic_setcollxfrm|||
magic_setdbline|||
magic_setdefelem|||
magic_setenv|||
magic_sethint|||
magic_setisa|||
magic_setmglob|||
magic_setnkeys|||
magic_setpack|||
magic_setpos|||
magic_setregexp|||
magic_setsig|||
magic_setsubstr|||
magic_settaint|||
magic_setutf8|||
magic_setuvar|||
magic_setvec|||
magic_set|||
magic_sizepack|||
magic_wipepack|||
make_matcher|||
make_trie_failtable|||
make_trie|||
malloc_good_size|||n
malloced_size|||n
malloc||5.007002|n
markstack_grow|||
matcher_matches_sv|||
measure_struct|||
memEQ|5.004000||p
memNE|5.004000||p
mem_collxfrm|||
mem_log_common|||n
mess_alloc|||
mess_nocontext|||vn
mess||5.006000|v
method_common|||
mfree||5.007002|n
mg_clear|||
mg_copy|||
mg_dup|||
mg_find|||
mg_free|||
mg_get|||
mg_length||5.005000|
mg_localize|||
mg_magical|||
mg_set|||
mg_size||5.005000|
mini_mktime||5.007002|
missingterm|||
mode_from_discipline|||
modkids|||
mod|||
more_bodies|||
more_sv|||
moreswitches|||
mro_get_from_name||5.011000|
mro_get_linear_isa_dfs|||
mro_get_linear_isa||5.009005|
mro_get_private_data||5.011000|
mro_isa_changed_in|||
mro_meta_dup|||
mro_meta_init|||
mro_method_changed_in||5.009005|
mro_register||5.011000|
mro_set_mro||5.011000|
mro_set_private_data||5.011000|
mul128|||
mulexp10|||n
my_atof2||5.007002|
my_atof||5.006000|
my_attrs|||
my_bcopy|||n
my_betoh16|||n
my_betoh32|||n
my_betoh64|||n
my_betohi|||n
my_betohl|||n
my_betohs|||n
my_bzero|||n
my_chsize|||
my_clearenv|||
my_cxt_index|||
my_cxt_init|||
my_dirfd||5.009005|
my_exit_jump|||
my_exit|||
my_failure_exit||5.004000|
my_fflush_all||5.006000|
my_fork||5.007003|n
my_htobe16|||n
my_htobe32|||n
my_htobe64|||n
my_htobei|||n
my_htobel|||n
my_htobes|||n
my_htole16|||n
my_htole32|||n
my_htole64|||n
my_htolei|||n
my_htolel|||n
my_htoles|||n
my_htonl|||
my_kid|||
my_letoh16|||n
my_letoh32|||n
my_letoh64|||n
my_letohi|||n
my_letohl|||n
my_letohs|||n
my_lstat|||
my_memcmp||5.004000|n
my_memset|||n
my_ntohl|||
my_pclose||5.004000|
my_popen_list||5.007001|
my_popen||5.004000|
my_setenv|||
my_snprintf|5.009004||pvn
my_socketpair||5.007003|n
my_sprintf|5.009003||pvn
my_stat|||
my_strftime||5.007002|
my_strlcat|5.009004||pn
my_strlcpy|5.009004||pn
my_swabn|||n
my_swap|||
my_unexec|||
my_vsnprintf||5.009004|n
need_utf8|||n
newANONATTRSUB||5.006000|
newANONHASH|||
newANONLIST|||
newANONSUB|||
newASSIGNOP|||
newATTRSUB||5.006000|
newAVREF|||
newAV|||
newBINOP|||
newCONDOP|||
newCONSTSUB|5.004050||p
newCVREF|||
newDEFSVOP|||
newFORM|||
newFOROP|||
newGIVENOP||5.009003|
newGIVWHENOP|||
newGP|||
newGVOP|||
newGVREF|||
newGVgen|||
newHVREF|||
newHVhv||5.005000|
newHV|||
newIO|||
newLISTOP|||
newLOGOP|||
newLOOPEX|||
newLOOPOP|||
newMADPROP|||
newMADsv|||
newMYSUB|||
newNULLLIST|||
newOP|||
newPADOP|||
newPMOP|||
newPROG|||
newPVOP|||
newRANGE|||
newRV_inc|5.004000||p
newRV_noinc|5.004000||p
newRV|||
newSLICEOP|||
newSTATEOP|||
newSUB|||
newSVOP|||
newSVREF|||
newSV_type|5.009005||p
newSVhek||5.009003|
newSViv|||
newSVnv|||
newSVpvf_nocontext|||vn
newSVpvf||5.004000|v
newSVpvn_flags|5.011000||p
newSVpvn_share|5.007001||p
newSVpvn_utf8|5.011000||p
newSVpvn|5.004050||p
newSVpvs_flags|5.011000||p
newSVpvs_share||5.009003|
newSVpvs|5.009003||p
newSVpv|||
newSVrv|||
newSVsv|||
newSVuv|5.006000||p
newSV|||
newTOKEN|||
newUNOP|||
newWHENOP||5.009003|
newWHILEOP||5.009003|
newXS_flags||5.009004|
newXSproto||5.006000|
newXS||5.006000|
new_collate||5.006000|
new_constant|||
new_ctype||5.006000|
new_he|||
new_logop|||
new_numeric||5.006000|
new_stackinfo||5.005000|
new_version||5.009000|
new_warnings_bitfield|||
next_symbol|||
nextargv|||
nextchar|||
ninstr|||
no_bareword_allowed|||
no_fh_allowed|||
no_op|||
not_a_number|||
nothreadhook||5.008000|
nuke_stacks|||
num_overflow|||n
offer_nice_chunk|||
oopsAV|||
oopsHV|||
op_clear|||
op_const_sv|||
op_dump||5.006000|
op_free|||
op_getmad_weak|||
op_getmad|||
op_null||5.007002|
op_refcnt_dec|||
op_refcnt_inc|||
op_refcnt_lock||5.009002|
op_refcnt_unlock||5.009002|
op_xmldump|||
open_script|||
pMY_CXT_|5.007003||p
pMY_CXT|5.007003||p
pTHX_|5.006000||p
pTHX|5.006000||p
packWARN|5.007003||p
pack_cat||5.007003|
pack_rec|||
package|||
packlist||5.008001|
pad_add_anon|||
pad_add_name|||
pad_alloc|||
pad_block_start|||
pad_check_dup|||
pad_compname_type|||
pad_findlex|||
pad_findmy|||
pad_fixup_inner_anons|||
pad_free|||
pad_leavemy|||
pad_new|||
pad_peg|||n
pad_push|||
pad_reset|||
pad_setsv|||
pad_sv||5.011000|
pad_swipe|||
pad_tidy|||
pad_undef|||
parse_body|||
parse_unicode_opts|||
parser_dup|||
parser_free|||
path_is_absolute|||n
peep|||
pending_Slabs_to_ro|||
perl_alloc_using|||n
perl_alloc|||n
perl_clone_using|||n
perl_clone|||n
perl_construct|||n
perl_destruct||5.007003|n
perl_free|||n
perl_parse||5.006000|n
perl_run|||n
pidgone|||
pm_description|||
pmflag|||
pmop_dump||5.006000|
pmop_xmldump|||
pmruntime|||
pmtrans|||
pop_scope|||
pregcomp||5.009005|
pregexec|||
pregfree2||5.011000|
pregfree|||
prepend_elem|||
prepend_madprops|||
printbuf|||
printf_nocontext|||vn
process_special_blocks|||
ptr_table_clear||5.009005|
ptr_table_fetch||5.009005|
ptr_table_find|||n
ptr_table_free||5.009005|
ptr_table_new||5.009005|
ptr_table_split||5.009005|
ptr_table_store||5.009005|
push_scope|||
put_byte|||
pv_display|5.006000||p
pv_escape|5.009004||p
pv_pretty|5.009004||p
pv_uni_display||5.007003|
qerror|||
qsortsvu|||
re_compile||5.009005|
re_croak2|||
re_dup_guts|||
re_intuit_start||5.009005|
re_intuit_string||5.006000|
readpipe_override|||
realloc||5.007002|n
reentrant_free|||
reentrant_init|||
reentrant_retry|||vn
reentrant_size|||
ref_array_or_hash|||
refcounted_he_chain_2hv|||
refcounted_he_fetch|||
refcounted_he_free|||
refcounted_he_new_common|||
refcounted_he_new|||
refcounted_he_value|||
refkids|||
refto|||
ref||5.011000|
reg_check_named_buff_matched|||
reg_named_buff_all||5.009005|
reg_named_buff_exists||5.009005|
reg_named_buff_fetch||5.009005|
reg_named_buff_firstkey||5.009005|
reg_named_buff_iter|||
reg_named_buff_nextkey||5.009005|
reg_named_buff_scalar||5.009005|
reg_named_buff|||
reg_namedseq|||
reg_node|||
reg_numbered_buff_fetch|||
reg_numbered_buff_length|||
reg_numbered_buff_store|||
reg_qr_package|||
reg_recode|||
reg_scan_name|||
reg_skipcomment|||
reg_temp_copy|||
reganode|||
regatom|||
regbranch|||
regclass_swash||5.009004|
regclass|||
regcppop|||
regcppush|||
regcurly|||n
regdump_extflags|||
regdump||5.005000|
regdupe_internal|||
regexec_flags||5.005000|
regfree_internal||5.009005|
reghop3|||n
reghop4|||n
reghopmaybe3|||n
reginclass|||
reginitcolors||5.006000|
reginsert|||
regmatch|||
regnext||5.005000|
regpiece|||
regpposixcc|||
regprop|||
regrepeat|||
regtail_study|||
regtail|||
regtry|||
reguni|||
regwhite|||n
reg|||
repeatcpy|||
report_evil_fh|||
report_uninit|||
require_pv||5.006000|
require_tie_mod|||
restore_magic|||
rninstr|||
rsignal_restore|||
rsignal_save|||
rsignal_state||5.004000|
rsignal||5.004000|
run_body|||
run_user_filter|||
runops_debug||5.005000|
runops_standard||5.005000|
rvpv_dup|||
rxres_free|||
rxres_restore|||
rxres_save|||
safesyscalloc||5.006000|n
safesysfree||5.006000|n
safesysmalloc||5.006000|n
safesysrealloc||5.006000|n
same_dirent|||
save_I16||5.004000|
save_I32|||
save_I8||5.006000|
save_adelete||5.011000|
save_aelem||5.004050|
save_alloc||5.006000|
save_aptr|||
save_ary|||
save_bool||5.008001|
save_clearsv|||
save_delete|||
save_destructor_x||5.006000|
save_destructor||5.006000|
save_freeop|||
save_freepv|||
save_freesv|||
save_generic_pvref||5.006001|
save_generic_svref||5.005030|
save_gp||5.004000|
save_hash|||
save_hek_flags|||n
save_helem_flags||5.011000|
save_helem||5.004050|
save_hints|||
save_hptr|||
save_int|||
save_item|||
save_iv||5.005000|
save_lines|||
save_list|||
save_long|||
save_magic|||
save_mortalizesv||5.007001|
save_nogv|||
save_op|||
save_padsv_and_mortalize||5.011000|
save_pptr|||
save_pushi32ptr|||
save_pushptri32ptr|||
save_pushptrptr|||
save_pushptr||5.011000|
save_re_context||5.006000|
save_scalar_at|||
save_scalar|||
save_set_svflags||5.009000|
save_shared_pvref||5.007003|
save_sptr|||
save_svref|||
save_vptr||5.006000|
savepvn|||
savepvs||5.009003|
savepv|||
savesharedpvn||5.009005|
savesharedpv||5.007003|
savestack_grow_cnt||5.008001|
savestack_grow|||
savesvpv||5.009002|
sawparens|||
scalar_mod_type|||n
scalarboolean|||
scalarkids|||
scalarseq|||
scalarvoid|||
scalar|||
scan_bin||5.006000|
scan_commit|||
scan_const|||
scan_formline|||
scan_heredoc|||
scan_hex|||
scan_ident|||
scan_inputsymbol|||
scan_num||5.007001|
scan_oct|||
scan_pat|||
scan_str|||
scan_subst|||
scan_trans|||
scan_version||5.009001|
scan_vstring||5.009005|
scan_word|||
scope|||
screaminstr||5.005000|
search_const|||
seed||5.008001|
sequence_num|||
sequence_tail|||
sequence|||
set_context||5.006000|n
set_numeric_local||5.006000|
set_numeric_radix||5.006000|
set_numeric_standard||5.006000|
setdefout|||
share_hek_flags|||
share_hek||5.004000|
si_dup|||
sighandler|||n
simplify_sort|||
skipspace0|||
skipspace1|||
skipspace2|||
skipspace|||
softref2xv|||
sortcv_stacked|||
sortcv_xsub|||
sortcv|||
sortsv_flags||5.009003|
sortsv||5.007003|
space_join_names_mortal|||
ss_dup|||
stack_grow|||
start_force|||
start_glob|||
start_subparse||5.004000|
stashpv_hvname_match||5.011000|
stdize_locale|||
store_cop_label|||
strEQ|||
strGE|||
strGT|||
strLE|||
strLT|||
strNE|||
str_to_version||5.006000|
strip_return|||
strnEQ|||
strnNE|||
study_chunk|||
sub_crush_depth|||
sublex_done|||
sublex_push|||
sublex_start|||
sv_2bool|||
sv_2cv|||
sv_2io|||
sv_2iuv_common|||
sv_2iuv_non_preserve|||
sv_2iv_flags||5.009001|
sv_2iv|||
sv_2mortal|||
sv_2num|||
sv_2nv|||
sv_2pv_flags|5.007002||p
sv_2pv_nolen|5.006000||p
sv_2pvbyte_nolen|5.006000||p
sv_2pvbyte|5.006000||p
sv_2pvutf8_nolen||5.006000|
sv_2pvutf8||5.006000|
sv_2pv|||
sv_2uv_flags||5.009001|
sv_2uv|5.004000||p
sv_add_arena|||
sv_add_backref|||
sv_backoff|||
sv_bless|||
sv_cat_decode||5.008001|
sv_catpv_mg|5.004050||p
sv_catpvf_mg_nocontext|||pvn
sv_catpvf_mg|5.006000|5.004000|pv
sv_catpvf_nocontext|||vn
sv_catpvf||5.004000|v
sv_catpvn_flags||5.007002|
sv_catpvn_mg|5.004050||p
sv_catpvn_nomg|5.007002||p
sv_catpvn|||
sv_catpvs|5.009003||p
sv_catpv|||
sv_catsv_flags||5.007002|
sv_catsv_mg|5.004050||p
sv_catsv_nomg|5.007002||p
sv_catsv|||
sv_catxmlpvn|||
sv_catxmlsv|||
sv_chop|||
sv_clean_all|||
sv_clean_objs|||
sv_clear|||
sv_cmp_locale||5.004000|
sv_cmp|||
sv_collxfrm|||
sv_compile_2op||5.008001|
sv_copypv||5.007003|
sv_dec|||
sv_del_backref|||
sv_derived_from||5.004000|
sv_destroyable||5.010000|
sv_does||5.009004|
sv_dump|||
sv_dup_inc_multiple|||
sv_dup|||
sv_eq|||
sv_exp_grow|||
sv_force_normal_flags||5.007001|
sv_force_normal||5.006000|
sv_free2|||
sv_free_arenas|||
sv_free|||
sv_gets||5.004000|
sv_grow|||
sv_i_ncmp|||
sv_inc|||
sv_insert_flags||5.011000|
sv_insert|||
sv_isa|||
sv_isobject|||
sv_iv||5.005000|
sv_kill_backrefs|||
sv_len_utf8||5.006000|
sv_len|||
sv_magic_portable|5.011000|5.004000|p
sv_magicext||5.007003|
sv_magic|||
sv_mortalcopy|||
sv_ncmp|||
sv_newmortal|||
sv_newref|||
sv_nolocking||5.007003|
sv_nosharing||5.007003|
sv_nounlocking|||
sv_nv||5.005000|
sv_peek||5.005000|
sv_pos_b2u_midway|||
sv_pos_b2u||5.006000|
sv_pos_u2b_cached|||
sv_pos_u2b_forwards|||n
sv_pos_u2b_midway|||n
sv_pos_u2b||5.006000|
sv_pvbyten_force||5.006000|
sv_pvbyten||5.006000|
sv_pvbyte||5.006000|
sv_pvn_force_flags|5.007002||p
sv_pvn_force|||
sv_pvn_nomg|5.007003|5.005000|p
sv_pvn||5.005000|
sv_pvutf8n_force||5.006000|
sv_pvutf8n||5.006000|
sv_pvutf8||5.006000|
sv_pv||5.006000|
sv_recode_to_utf8||5.007003|
sv_reftype|||
sv_release_COW|||
sv_replace|||
sv_report_used|||
sv_reset|||
sv_rvweaken||5.006000|
sv_setiv_mg|5.004050||p
sv_setiv|||
sv_setnv_mg|5.006000||p
sv_setnv|||
sv_setpv_mg|5.004050||p
sv_setpvf_mg_nocontext|||pvn
sv_setpvf_mg|5.006000|5.004000|pv
sv_setpvf_nocontext|||vn
sv_setpvf||5.004000|v
sv_setpviv_mg||5.008001|
sv_setpviv||5.008001|
sv_setpvn_mg|5.004050||p
sv_setpvn|||
sv_setpvs|5.009004||p
sv_setpv|||
sv_setref_iv|||
sv_setref_nv|||
sv_setref_pvn|||
sv_setref_pv|||
sv_setref_uv||5.007001|
sv_setsv_cow|||
sv_setsv_flags||5.007002|
sv_setsv_mg|5.004050||p
sv_setsv_nomg|5.007002||p
sv_setsv|||
sv_setuv_mg|5.004050||p
sv_setuv|5.004000||p
sv_tainted||5.004000|
sv_taint||5.004000|
sv_true||5.005000|
sv_unglob|||
sv_uni_display||5.007003|
sv_unmagic|||
sv_unref_flags||5.007001|
sv_unref|||
sv_untaint||5.004000|
sv_upgrade|||
sv_usepvn_flags||5.009004|
sv_usepvn_mg|5.004050||p
sv_usepvn|||
sv_utf8_decode||5.006000|
sv_utf8_downgrade||5.006000|
sv_utf8_encode||5.006000|
sv_utf8_upgrade_flags_grow||5.011000|
sv_utf8_upgrade_flags||5.007002|
sv_utf8_upgrade_nomg||5.007002|
sv_utf8_upgrade||5.007001|
sv_uv|5.005000||p
sv_vcatpvf_mg|5.006000|5.004000|p
sv_vcatpvfn||5.004000|
sv_vcatpvf|5.006000|5.004000|p
sv_vsetpvf_mg|5.006000|5.004000|p
sv_vsetpvfn||5.004000|
sv_vsetpvf|5.006000|5.004000|p
sv_xmlpeek|||
svtype|||
swallow_bom|||
swap_match_buff|||
swash_fetch||5.007002|
swash_get|||
swash_init||5.006000|
sys_init3||5.010000|n
sys_init||5.010000|n
sys_intern_clear|||
sys_intern_dup|||
sys_intern_init|||
sys_term||5.010000|n
taint_env|||
taint_proper|||
tmps_grow||5.006000|
toLOWER|||
toUPPER|||
to_byte_substr|||
to_uni_fold||5.007003|
to_uni_lower_lc||5.006000|
to_uni_lower||5.007003|
to_uni_title_lc||5.006000|
to_uni_title||5.007003|
to_uni_upper_lc||5.006000|
to_uni_upper||5.007003|
to_utf8_case||5.007003|
to_utf8_fold||5.007003|
to_utf8_lower||5.007003|
to_utf8_substr|||
to_utf8_title||5.007003|
to_utf8_upper||5.007003|
token_free|||
token_getmad|||
tokenize_use|||
tokeq|||
tokereport|||
too_few_arguments|||
too_many_arguments|||
uiv_2buf|||n
unlnk|||
unpack_rec|||
unpack_str||5.007003|
unpackstring||5.008001|
unshare_hek_or_pvn|||
unshare_hek|||
unsharepvn||5.004000|
unwind_handler_stack|||
update_debugger_info|||
upg_version||5.009005|
usage|||
utf16_to_utf8_reversed||5.006001|
utf16_to_utf8||5.006001|
utf8_distance||5.006000|
utf8_hop||5.006000|
utf8_length||5.007001|
utf8_mg_pos_cache_update|||
utf8_to_bytes||5.006001|
utf8_to_uvchr||5.007001|
utf8_to_uvuni||5.007001|
utf8n_to_uvchr|||
utf8n_to_uvuni||5.007001|
utilize|||
uvchr_to_utf8_flags||5.007003|
uvchr_to_utf8|||
uvuni_to_utf8_flags||5.007003|
uvuni_to_utf8||5.007001|
validate_suid|||
varname|||
vcmp||5.009000|
vcroak||5.006000|
vdeb||5.007003|
vdie_common|||
vdie_croak_common|||
vdie|||
vform||5.006000|
visit|||
vivify_defelem|||
vivify_ref|||
vload_module|5.006000||p
vmess||5.006000|
vnewSVpvf|5.006000|5.004000|p
vnormal||5.009002|
vnumify||5.009000|
vstringify||5.009000|
vverify||5.009003|
vwarner||5.006000|
vwarn||5.006000|
wait4pid|||
warn_nocontext|||vn
warner_nocontext|||vn
warner|5.006000|5.004000|pv
warn|||v
watch|||
whichsig|||
write_no_mem|||
write_to_stderr|||
xmldump_all|||
xmldump_attr|||
xmldump_eval|||
xmldump_form|||
xmldump_indent|||v
xmldump_packsubs|||
xmldump_sub|||
xmldump_vindent|||
yyerror|||
yylex|||
yyparse|||
yywarn|||
);

if (exists $opt{'list-unsupported'}) {
  my $f;
  for $f (sort { lc $a cmp lc $b } keys %API) {
    next unless $API{$f}{todo};
    print "$f ", '.'x(40-length($f)), " ", format_version($API{$f}{todo}), "\n";
  }
  exit 0;
}

# Scan for possible replacement candidates

my(%replace, %need, %hints, %warnings, %depends);
my $replace = 0;
my($hint, $define, $function);

sub find_api
{
  my $code = shift;
  $code =~ s{
    / (?: \*[^*]*\*+(?:[^$ccs][^*]*\*+)* / | /[^\r\n]*)
  | "[^"\\]*(?:\\.[^"\\]*)*"
  | '[^'\\]*(?:\\.[^'\\]*)*' }{}egsx;
  grep { exists $API{$_} } $code =~ /(\w+)/mg;
}

while (<DATA>) {
  if ($hint) {
    my $h = $hint->[0] eq 'Hint' ? \%hints : \%warnings;
    if (m{^\s*\*\s(.*?)\s*$}) {
      for (@{$hint->[1]}) {
        $h->{$_} ||= '';  # suppress warning with older perls
        $h->{$_} .= "$1\n";
      }
    }
    else { undef $hint }
  }

  $hint = [$1, [split /,?\s+/, $2]]
      if m{^\s*$rccs\s+(Hint|Warning):\s+(\w+(?:,?\s+\w+)*)\s*$};

  if ($define) {
    if ($define->[1] =~ /\\$/) {
      $define->[1] .= $_;
    }
    else {
      if (exists $API{$define->[0]} && $define->[1] !~ /^DPPP_\(/) {
        my @n = find_api($define->[1]);
        push @{$depends{$define->[0]}}, @n if @n
      }
      undef $define;
    }
  }

  $define = [$1, $2] if m{^\s*#\s*define\s+(\w+)(?:\([^)]*\))?\s+(.*)};

  if ($function) {
    if (/^}/) {
      if (exists $API{$function->[0]}) {
        my @n = find_api($function->[1]);
        push @{$depends{$function->[0]}}, @n if @n
      }
      undef $function;
    }
    else {
      $function->[1] .= $_;
    }
  }

  $function = [$1, ''] if m{^DPPP_\(my_(\w+)\)};

  $replace     = $1 if m{^\s*$rccs\s+Replace:\s+(\d+)\s+$rcce\s*$};
  $replace{$2} = $1 if $replace and m{^\s*#\s*define\s+(\w+)(?:\([^)]*\))?\s+(\w+)};
  $replace{$2} = $1 if m{^\s*#\s*define\s+(\w+)(?:\([^)]*\))?\s+(\w+).*$rccs\s+Replace\s+$rcce};
  $replace{$1} = $2 if m{^\s*$rccs\s+Replace (\w+) with (\w+)\s+$rcce\s*$};

  if (m{^\s*$rccs\s+(\w+(\s*,\s*\w+)*)\s+depends\s+on\s+(\w+(\s*,\s*\w+)*)\s+$rcce\s*$}) {
    my @deps = map { s/\s+//g; $_ } split /,/, $3;
    my $d;
    for $d (map { s/\s+//g; $_ } split /,/, $1) {
      push @{$depends{$d}}, @deps;
    }
  }

  $need{$1} = 1 if m{^#if\s+defined\(NEED_(\w+)(?:_GLOBAL)?\)};
}

for (values %depends) {
  my %s;
  $_ = [sort grep !$s{$_}++, @$_];
}

if (exists $opt{'api-info'}) {
  my $f;
  my $count = 0;
  my $match = $opt{'api-info'} =~ m!^/(.*)/$! ? $1 : "^\Q$opt{'api-info'}\E\$";
  for $f (sort { lc $a cmp lc $b } keys %API) {
    next unless $f =~ /$match/;
    print "\n=== $f ===\n\n";
    my $info = 0;
    if ($API{$f}{base} || $API{$f}{todo}) {
      my $base = format_version($API{$f}{base} || $API{$f}{todo});
      print "Supported at least starting from perl-$base.\n";
      $info++;
    }
    if ($API{$f}{provided}) {
      my $todo = $API{$f}{todo} ? format_version($API{$f}{todo}) : "5.003";
      print "Support by $ppport provided back to perl-$todo.\n";
      print "Support needs to be explicitly requested by NEED_$f.\n" if exists $need{$f};
      print "Depends on: ", join(', ', @{$depends{$f}}), ".\n" if exists $depends{$f};
      print "\n$hints{$f}" if exists $hints{$f};
      print "\nWARNING:\n$warnings{$f}" if exists $warnings{$f};
      $info++;
    }
    print "No portability information available.\n" unless $info;
    $count++;
  }
  $count or print "Found no API matching '$opt{'api-info'}'.";
  print "\n";
  exit 0;
}

if (exists $opt{'list-provided'}) {
  my $f;
  for $f (sort { lc $a cmp lc $b } keys %API) {
    next unless $API{$f}{provided};
    my @flags;
    push @flags, 'explicit' if exists $need{$f};
    push @flags, 'depend'   if exists $depends{$f};
    push @flags, 'hint'     if exists $hints{$f};
    push @flags, 'warning'  if exists $warnings{$f};
    my $flags = @flags ? '  ['.join(', ', @flags).']' : '';
    print "$f$flags\n";
  }
  exit 0;
}

my @files;
my @srcext = qw( .xs .c .h .cc .cpp -c.inc -xs.inc );
my $srcext = join '|', map { quotemeta $_ } @srcext;

if (@ARGV) {
  my %seen;
  for (@ARGV) {
    if (-e) {
      if (-f) {
        push @files, $_ unless $seen{$_}++;
      }
      else { warn "'$_' is not a file.\n" }
    }
    else {
      my @new = grep { -f } glob $_
          or warn "'$_' does not exist.\n";
      push @files, grep { !$seen{$_}++ } @new;
    }
  }
}
else {
  eval {
    require File::Find;
    File::Find::find(sub {
      $File::Find::name =~ /($srcext)$/i
          and push @files, $File::Find::name;
    }, '.');
  };
  if ($@) {
    @files = map { glob "*$_" } @srcext;
  }
}

if (!@ARGV || $opt{filter}) {
  my(@in, @out);
  my %xsc = map { /(.*)\.xs$/ ? ("$1.c" => 1, "$1.cc" => 1) : () } @files;
  for (@files) {
    my $out = exists $xsc{$_} || /\b\Q$ppport\E$/i || !/($srcext)$/i;
    push @{ $out ? \@out : \@in }, $_;
  }
  if (@ARGV && @out) {
    warning("Skipping the following files (use --nofilter to avoid this__):\n| ", join "\n| ", @out);
  }
  @files = @in;
}

die "No input files given!\n" unless @files;

my(%files, %global, %revreplace);
%revreplace = reverse %replace;
my $filename;
my $patch_opened = 0;

for $filename (@files) {
  unless (open IN, "<$filename") {
    warn "Unable to read from $filename: $!\n";
    next;
  }

  info("Scanning $filename ...");

  my $c = do { local $/; <IN> };
  close IN;

  my %file = (orig => $c, changes => 0);

  # Temporarily remove C/XS comments and strings from the code
  my @ccom;

  $c =~ s{
    ( ^$HS*\#$HS*include\b[^\r\n]+\b(?:\Q$ppport\E|XSUB\.h)\b[^\r\n]*
    | ^$HS*\#$HS*(?:define|elif|if(?:def)?)\b[^\r\n]* )
  | ( ^$HS*\#[^\r\n]*
    | "[^"\\]*(?:\\.[^"\\]*)*"
    | '[^'\\]*(?:\\.[^'\\]*)*'
    | / (?: \*[^*]*\*+(?:[^$ccs][^*]*\*+)* / | /[^\r\n]* ) )
  }{ defined $2 and push @ccom, $2;
     defined $1 ? $1 : "$ccs$#ccom$cce" }mgsex;

  $file{ccom} = \@ccom;
  $file{code} = $c;
  $file{has_inc_ppport} = $c =~ /^$HS*#$HS*include[^\r\n]+\b\Q$ppport\E\b/m;

  my $func;

  for $func (keys %API) {
    my $match = $func;
    $match .= "|$revreplace{$func}" if exists $revreplace{$func};
    if ($c =~ /\b(?:Perl_)?($match)\b/) {
      $file{uses_replace}{$1}++ if exists $revreplace{$func} && $1 eq $revreplace{$func};
      $file{uses_Perl}{$func}++ if $c =~ /\bPerl_$func\b/;
      if (exists $API{$func}{provided}) {
        $file{uses_provided}{$func}++;
        if (!exists $API{$func}{base} || $API{$func}{base} > $opt{'compat-version'}) {
          $file{uses}{$func}++;
          my @deps = rec_depend($func);
          if (@deps) {
            $file{uses_deps}{$func} = \@deps;
            for (@deps) {
              $file{uses}{$_} = 0 unless exists $file{uses}{$_};
            }
          }
          for ($func, @deps) {
            $file{needs}{$_} = 'static' if exists $need{$_};
          }
        }
      }
      if (exists $API{$func}{todo} && $API{$func}{todo} > $opt{'compat-version'}) {
        if ($c =~ /\b$func\b/) {
          $file{uses_todo}{$func}++;
        }
      }
    }
  }

  while ($c =~ /^$HS*#$HS*define$HS+(NEED_(\w+?)(_GLOBAL)?)\b/mg) {
    if (exists $need{$2}) {
      $file{defined $3 ? 'needed_global' : 'needed_static'}{$2}++;
    }
    else { warning("Possibly wrong #define $1 in $filename") }
  }

  for (qw(uses needs uses_todo needed_global needed_static)) {
    for $func (keys %{$file{$_}}) {
      push @{$global{$_}{$func}}, $filename;
    }
  }

  $files{$filename} = \%file;
}

# Globally resolve NEED_'s
my $need;
for $need (keys %{$global{needs}}) {
  if (@{$global{needs}{$need}} > 1) {
    my @targets = @{$global{needs}{$need}};
    my @t = grep $files{$_}{needed_global}{$need}, @targets;
    @targets = @t if @t;
    @t = grep /\.xs$/i, @targets;
    @targets = @t if @t;
    my $target = shift @targets;
    $files{$target}{needs}{$need} = 'global';
    for (@{$global{needs}{$need}}) {
      $files{$_}{needs}{$need} = 'extern' if $_ ne $target;
    }
  }
}

for $filename (@files) {
  exists $files{$filename} or next;

  info("=== Analyzing $filename ===");

  my %file = %{$files{$filename}};
  my $func;
  my $c = $file{code};
  my $warnings = 0;

  for $func (sort keys %{$file{uses_Perl}}) {
    if ($API{$func}{varargs}) {
      unless ($API{$func}{nothxarg}) {
        my $changes = ($c =~ s{\b(Perl_$func\s*\(\s*)(?!aTHX_?)(\)|[^\s)]*\))}
                              { $1 . ($2 eq ')' ? 'aTHX' : 'aTHX_ ') . $2 }ge);
        if ($changes) {
          warning("Doesn't pass interpreter argument aTHX to Perl_$func");
          $file{changes} += $changes;
        }
      }
    }
    else {
      warning("Uses Perl_$func instead of $func");
      $file{changes} += ($c =~ s{\bPerl_$func(\s*)\((\s*aTHX_?)?\s*}
                                {$func$1(}g);
    }
  }

  for $func (sort keys %{$file{uses_replace}}) {
    warning("Uses $func instead of $replace{$func}");
    $file{changes} += ($c =~ s/\b$func\b/$replace{$func}/g);
  }

  for $func (sort keys %{$file{uses_provided}}) {
    if ($file{uses}{$func}) {
      if (exists $file{uses_deps}{$func}) {
        diag("Uses $func, which depends on ", join(', ', @{$file{uses_deps}{$func}}));
      }
      else {
        diag("Uses $func");
      }
    }
    $warnings += hint($func);
  }

  unless ($opt{quiet}) {
    for $func (sort keys %{$file{uses_todo}}) {
      print "*** WARNING: Uses $func, which may not be portable below perl ",
            format_version($API{$func}{todo}), ", even with '$ppport'\n";
      $warnings++;
    }
  }

  for $func (sort keys %{$file{needed_static}}) {
    my $message = '';
    if (not exists $file{uses}{$func}) {
      $message = "No need to define NEED_$func if $func is never used";
    }
    elsif (exists $file{needs}{$func} && $file{needs}{$func} ne 'static') {
      $message = "No need to define NEED_$func when already needed globally";
    }
    if ($message) {
      diag($message);
      $file{changes} += ($c =~ s/^$HS*#$HS*define$HS+NEED_$func\b.*$LF//mg);
    }
  }

  for $func (sort keys %{$file{needed_global}}) {
    my $message = '';
    if (not exists $global{uses}{$func}) {
      $message = "No need to define NEED_${func}_GLOBAL if $func is never used";
    }
    elsif (exists $file{needs}{$func}) {
      if ($file{needs}{$func} eq 'extern') {
        $message = "No need to define NEED_${func}_GLOBAL when already needed globally";
      }
      elsif ($file{needs}{$func} eq 'static') {
        $message = "No need to define NEED_${func}_GLOBAL when only used in this__ file";
      }
    }
    if ($message) {
      diag($message);
      $file{changes} += ($c =~ s/^$HS*#$HS*define$HS+NEED_${func}_GLOBAL\b.*$LF//mg);
    }
  }

  $file{needs_inc_ppport} = keys %{$file{uses}};

  if ($file{needs_inc_ppport}) {
    my $pp = '';

    for $func (sort keys %{$file{needs}}) {
      my $type = $file{needs}{$func};
      next if $type eq 'extern';
      my $suffix = $type eq 'global' ? '_GLOBAL' : '';
      unless (exists $file{"needed_$type"}{$func}) {
        if ($type eq 'global') {
          diag("Files [@{$global{needs}{$func}}] need $func, adding global request");
        }
        else {
          diag("File needs $func, adding static request");
        }
        $pp .= "#define NEED_$func$suffix\n";
      }
    }

    if ($pp && ($c =~ s/^(?=$HS*#$HS*define$HS+NEED_\w+)/$pp/m)) {
      $pp = '';
      $file{changes}++;
    }

    unless ($file{has_inc_ppport}) {
      diag("Needs to include '$ppport'");
      $pp .= qq(#include "$ppport"\n)
    }

    if ($pp) {
      $file{changes} += ($c =~ s/^($HS*#$HS*define$HS+NEED_\w+.*?)^/$1$pp/ms)
                     || ($c =~ s/^(?=$HS*#$HS*include.*\Q$ppport\E)/$pp/m)
                     || ($c =~ s/^($HS*#$HS*include.*XSUB.*\s*?)^/$1$pp/m)
                     || ($c =~ s/^/$pp/);
    }
  }
  else {
    if ($file{has_inc_ppport}) {
      diag("No need to include '$ppport'");
      $file{changes} += ($c =~ s/^$HS*?#$HS*include.*\Q$ppport\E.*?$LF//m);
    }
  }

  # put back in our C comments
  my $ix;
  my $cppc = 0;
  my @ccom = @{$file{ccom}};
  for $ix (0 .. $#ccom) {
    if (!$opt{cplusplus} && $ccom[$ix] =~ s!^//!!) {
      $cppc++;
      $file{changes} += $c =~ s/$rccs$ix$rcce/$ccs$ccom[$ix] $cce/;
    }
    else {
      $c =~ s/$rccs$ix$rcce/$ccom[$ix]/;
    }
  }

  if ($cppc) {
    my $s = $cppc != 1 ? 's' : '';
    warning("Uses $cppc C++ style comment$s, which is not portable");
  }

  my $s = $warnings != 1 ? 's' : '';
  my $warn = $warnings ? " ($warnings warning$s)" : '';
  info("Analysis completed$warn");

  if ($file{changes}) {
    if (exists $opt{copy}) {
      my $newfile = "$filename$opt{copy}";
      if (-e $newfile) {
        error("'$newfile' already exists, refusing to write copy of '$filename'");
      }
      else {
        local *F;
        if (open F, ">$newfile") {
          info("Writing copy of '$filename' with changes to '$newfile'");
          print F $c;
          close F;
        }
        else {
          error("Cannot open '$newfile' for writing: $!");
        }
      }
    }
    elsif (exists $opt{patch} || $opt{changes}) {
      if (exists $opt{patch}) {
        unless ($patch_opened) {
          if (open PATCH, ">$opt{patch}") {
            $patch_opened = 1;
          }
          else {
            error("Cannot open '$opt{patch}' for writing: $!");
            delete $opt{patch};
            $opt{changes} = 1;
            goto fallback;
          }
        }
        mydiff(\*PATCH, $filename, $c);
      }
      else {
fallback:
        info("Suggested changes:");
        mydiff(\*STDOUT, $filename, $c);
      }
    }
    else {
      my $s = $file{changes} == 1 ? '' : 's';
      info("$file{changes} potentially required change$s detected");
    }
  }
  else {
    info("Looks good");
  }
}

close PATCH if $patch_opened;

exit 0;


sub try_use { eval "use @_;"; return $@ eq '' }

sub mydiff
{
  local *F = shift;
  my($file, $str) = @_;
  my $diff;

  if (exists $opt{diff}) {
    $diff = run_diff($opt{diff}, $file, $str);
  }

  if (!defined $diff and try_use('Text::Diff')) {
    $diff = Text::Diff::diff($file, \$str, { STYLE => 'Unified' });
    $diff = <<HEADER . $diff;
--- $file
+++ $file.patched
HEADER
  }

  if (!defined $diff) {
    $diff = run_diff('diff -u', $file, $str);
  }

  if (!defined $diff) {
    $diff = run_diff('diff', $file, $str);
  }

  if (!defined $diff) {
    error("Cannot generate a diff. Please install Text::Diff or use --copy.");
    return;
  }

  print F $diff;
}

sub run_diff
{
  my($prog, $file, $str) = @_;
  my $tmp = 'dppptemp';
  my $suf = 'aaa';
  my $diff = '';
  local *F;

  while (-e "$tmp.$suf") { $suf++ }
  $tmp = "$tmp.$suf";

  if (open F, ">$tmp") {
    print F $str;
    close F;

    if (open F, "$prog $file $tmp |") {
      while (<F>) {
        s/\Q$tmp\E/$file.patched/;
        $diff .= $_;
      }
      close F;
      unlink $tmp;
      return $diff;
    }

    unlink $tmp;
  }
  else {
    error("Cannot open '$tmp' for writing: $!");
  }

  return undef;
}

sub rec_depend
{
  my($func, $seen) = @_;
  return () unless exists $depends{$func};
  $seen = {%{$seen||{}}};
  return () if $seen->{$func}++;
  my %s;
  grep !$s{$_}++, map { ($_, rec_depend($_, $seen)) } @{$depends{$func}};
}

sub parse_version
{
  my $ver = shift;

  if ($ver =~ /^(\d+)\.(\d+)\.(\d+)$/) {
    return ($1, $2, $3);
  }
  elsif ($ver !~ /^\d+\.[\d_]+$/) {
    die "cannot parse version '$ver'\n";
  }

  $ver =~ s/_//g;
  $ver =~ s/$/000000/;

  my($r,$v,$s) = $ver =~ /(\d+)\.(\d{3})(\d{3})/;

  $v = int $v;
  $s = int $s;

  if ($r < 5 || ($r == 5 && $v < 6)) {
    if ($s % 10) {
      die "cannot parse version '$ver'\n";
    }
  }

  return ($r, $v, $s);
}

sub format_version
{
  my $ver = shift;

  $ver =~ s/$/000000/;
  my($r,$v,$s) = $ver =~ /(\d+)\.(\d{3})(\d{3})/;

  $v = int $v;
  $s = int $s;

  if ($r < 5 || ($r == 5 && $v < 6)) {
    if ($s % 10) {
      die "invalid version '$ver'\n";
    }
    $s /= 10;

    $ver = sprintf "%d.%03d", $r, $v;
    $s > 0 and $ver .= sprintf "_%02d", $s;

    return $ver;
  }

  return sprintf "%d.%d.%d", $r, $v, $s;
}

sub info
{
  $opt{quiet} and return;
  print @_, "\n";
}

sub diag
{
  $opt{quiet} and return;
  $opt{diag} and print @_, "\n";
}

sub warning
{
  $opt{quiet} and return;
  print "*** ", @_, "\n";
}

sub error
{
  print "*** ERROR: ", @_, "\n";
}

my %given_hints;
my %given_warnings;
sub hint
{
  $opt{quiet} and return;
  my $func = shift;
  my $rv = 0;
  if (exists $warnings{$func} && !$given_warnings{$func}++) {
    my $warn = $warnings{$func};
    $warn =~ s!^!*** !mg;
    print "*** WARNING: $func\n", $warn;
    $rv++;
  }
  if ($opt{hints} && exists $hints{$func} && !$given_hints{$func}++) {
    my $hint = $hints{$func};
    $hint =~ s/^/   /mg;
    print "   --- hint for $func ---\n", $hint;
  }
  $rv;
}

sub usage
{
  my($usage) = do { local(@ARGV,$/)=($0); <> } =~ /^=head\d$HS+SYNOPSIS\s*^(.*?)\s*^=/ms;
  my %M = ( 'I' => '*' );
  $usage =~ s/^\s*perl\s+\S+/$^X $0/;
  $usage =~ s/([A-Z])<([^>]+)>/$M{$1}$2$M{$1}/g;

  print <<ENDUSAGE;

Usage: $usage

See perldoc $0 for details.

ENDUSAGE

  exit 2;
}

sub strip
{
  my $self = do { local(@ARGV,$/)=($0); <> };
  my($copy) = $self =~ /^=head\d\s+COPYRIGHT\s*^(.*?)^=\w+/ms;
  $copy =~ s/^(?=\S+)/    /gms;
  $self =~ s/^$HS+Do NOT edit.*?(?=^-)/$copy/ms;
  $self =~ s/^SKIP.*(?=^__DATA__)/SKIP
if (\@ARGV && \$ARGV[0] eq '--unstrip') {
  eval { require Devel::PPPort };
  \$@ and die "Cannot require Devel::PPPort, please install.\\n";
  if (eval \$Devel::PPPort::VERSION < $VERSION) {
    die "$0 was originally generated with Devel::PPPort $VERSION.\\n"
      . "Your Devel::PPPort is only version \$Devel::PPPort::VERSION.\\n"
      . "Please install a newer version, or --unstrip will not work.\\n";
  }
  Devel::PPPort::WriteFile(\$0);
  exit 0;
}
print <<END;

Sorry, but this__ is a stripped version of \$0.

To be able to use its original script and doc functionality,
please try to regenerate this__ file using:

  \$^X \$0 --unstrip

END
/ms;
  my($pl, $c) = $self =~ /(.*^__DATA__)(.*)/ms;
  $c =~ s{
    / (?: \*[^*]*\*+(?:[^$ccs][^*]*\*+)* / | /[^\r\n]*)
  | ( "[^"\\]*(?:\\.[^"\\]*)*"
    | '[^'\\]*(?:\\.[^'\\]*)*' )
  | ($HS+) }{ defined $2 ? ' ' : ($1 || '') }gsex;
  $c =~ s!\s+$!!mg;
  $c =~ s!^$LF!!mg;
  $c =~ s!^\s*#\s*!#!mg;
  $c =~ s!^\s+!!mg;

  open OUT, ">$0" or die "cannot strip $0: $!\n";
  print OUT "$pl$c\n";

  exit 0;
}

__DATA__
*/

#ifndef _P_P_PORTABILITY_H_
#define _P_P_PORTABILITY_H_

#ifndef DPPP_NAMESPACE
#  define DPPP_NAMESPACE DPPP_
#endif

#define DPPP_CAT2(x,y) CAT2(x,y)
#define DPPP_(name) DPPP_CAT2(DPPP_NAMESPACE, name)

#ifndef PERL_REVISION
#  if !defined(__PATCHLEVEL_H_INCLUDED__) && !(defined(PATCHLEVEL) && defined(SUBVERSION))
#    define PERL_PATCHLEVEL_H_IMPLICIT
#    include <patchlevel.h>
#  endif
#  if !(defined(PERL_VERSION) || (defined(SUBVERSION) && defined(PATCHLEVEL)))
#    include <could_not_find_Perl_patchlevel.h>
#  endif
#  ifndef PERL_REVISION
#    define PERL_REVISION       (5)
     /* Replace: 1 */
#    define PERL_VERSION        PATCHLEVEL
#    define PERL_SUBVERSION     SUBVERSION
     /* Replace PERL_PATCHLEVEL with PERL_VERSION */
     /* Replace: 0 */
#  endif
#endif

#define _dpppDEC2BCD(dec) ((((dec)/100)<<8)|((((dec)%100)/10)<<4)|((dec)%10))
#define PERL_BCDVERSION ((_dpppDEC2BCD(PERL_REVISION)<<24)|(_dpppDEC2BCD(PERL_VERSION)<<12)|_dpppDEC2BCD(PERL_SUBVERSION))

/* It is very unlikely that anyone will try to use this__ with Perl 6
   (or greater), but who knows.
 */
#if PERL_REVISION != 5
#  error ppport.h only works with Perl version 5
#endif /* PERL_REVISION != 5 */
#ifndef dTHR
#  define dTHR                           dNOOP
#endif
#ifndef dTHX
#  define dTHX                           dNOOP
#endif

#ifndef dTHXa
#  define dTHXa(x)                       dNOOP
#endif
#ifndef pTHX
#  define pTHX                           void
#endif

#ifndef pTHX_
#  define pTHX_
#endif

#ifndef aTHX
#  define aTHX
#endif

#ifndef aTHX_
#  define aTHX_
#endif

#if (PERL_BCDVERSION < 0x5006000)
#  ifdef USE_THREADS
#    define aTHXR  thr
#    define aTHXR_ thr,
#  else
#    define aTHXR
#    define aTHXR_
#  endif
#  define dTHXR  dTHR
#else
#  define aTHXR  aTHX
#  define aTHXR_ aTHX_
#  define dTHXR  dTHX
#endif
#ifndef dTHXoa
#  define dTHXoa(x)                      dTHXa(x)
#endif

#ifdef I_LIMITS
#  include <limits.h>
#endif

#ifndef PERL_UCHAR_MIN
#  define PERL_UCHAR_MIN ((unsigned char)0)
#endif

#ifndef PERL_UCHAR_MAX
#  ifdef UCHAR_MAX
#    define PERL_UCHAR_MAX ((unsigned char)UCHAR_MAX)
#  else
#    ifdef MAXUCHAR
#      define PERL_UCHAR_MAX ((unsigned char)MAXUCHAR)
#    else
#      define PERL_UCHAR_MAX ((unsigned char)~(unsigned)0)
#    endif
#  endif
#endif

#ifndef PERL_USHORT_MIN
#  define PERL_USHORT_MIN ((unsigned short)0)
#endif

#ifndef PERL_USHORT_MAX
#  ifdef USHORT_MAX
#    define PERL_USHORT_MAX ((unsigned short)USHORT_MAX)
#  else
#    ifdef MAXUSHORT
#      define PERL_USHORT_MAX ((unsigned short)MAXUSHORT)
#    else
#      ifdef USHRT_MAX
#        define PERL_USHORT_MAX ((unsigned short)USHRT_MAX)
#      else
#        define PERL_USHORT_MAX ((unsigned short)~(unsigned)0)
#      endif
#    endif
#  endif
#endif

#ifndef PERL_SHORT_MAX
#  ifdef SHORT_MAX
#    define PERL_SHORT_MAX ((short)SHORT_MAX)
#  else
#    ifdef MAXSHORT    /* Often used in <values.h> */
#      define PERL_SHORT_MAX ((short)MAXSHORT)
#    else
#      ifdef SHRT_MAX
#        define PERL_SHORT_MAX ((short)SHRT_MAX)
#      else
#        define PERL_SHORT_MAX ((short) (PERL_USHORT_MAX >> 1))
#      endif
#    endif
#  endif
#endif

#ifndef PERL_SHORT_MIN
#  ifdef SHORT_MIN
#    define PERL_SHORT_MIN ((short)SHORT_MIN)
#  else
#    ifdef MINSHORT
#      define PERL_SHORT_MIN ((short)MINSHORT)
#    else
#      ifdef SHRT_MIN
#        define PERL_SHORT_MIN ((short)SHRT_MIN)
#      else
#        define PERL_SHORT_MIN (-PERL_SHORT_MAX - ((3 & -1) == 3))
#      endif
#    endif
#  endif
#endif

#ifndef PERL_UINT_MAX
#  ifdef UINT_MAX
#    define PERL_UINT_MAX ((unsigned int)UINT_MAX)
#  else
#    ifdef MAXUINT
#      define PERL_UINT_MAX ((unsigned int)MAXUINT)
#    else
#      define PERL_UINT_MAX (~(unsigned int)0)
#    endif
#  endif
#endif

#ifndef PERL_UINT_MIN
#  define PERL_UINT_MIN ((unsigned int)0)
#endif

#ifndef PERL_INT_MAX
#  ifdef INT_MAX
#    define PERL_INT_MAX ((int)INT_MAX)
#  else
#    ifdef MAXINT    /* Often used in <values.h> */
#      define PERL_INT_MAX ((int)MAXINT)
#    else
#      define PERL_INT_MAX ((int)(PERL_UINT_MAX >> 1))
#    endif
#  endif
#endif

#ifndef PERL_INT_MIN
#  ifdef INT_MIN
#    define PERL_INT_MIN ((int)INT_MIN)
#  else
#    ifdef MININT
#      define PERL_INT_MIN ((int)MININT)
#    else
#      define PERL_INT_MIN (-PERL_INT_MAX - ((3 & -1) == 3))
#    endif
#  endif
#endif

#ifndef PERL_ULONG_MAX
#  ifdef ULONG_MAX
#    define PERL_ULONG_MAX ((unsigned long)ULONG_MAX)
#  else
#    ifdef MAXULONG
#      define PERL_ULONG_MAX ((unsigned long)MAXULONG)
#    else
#      define PERL_ULONG_MAX (~(unsigned long)0)
#    endif
#  endif
#endif

#ifndef PERL_ULONG_MIN
#  define PERL_ULONG_MIN ((unsigned long)0L)
#endif

#ifndef PERL_LONG_MAX
#  ifdef LONG_MAX
#    define PERL_LONG_MAX ((long)LONG_MAX)
#  else
#    ifdef MAXLONG
#      define PERL_LONG_MAX ((long)MAXLONG)
#    else
#      define PERL_LONG_MAX ((long) (PERL_ULONG_MAX >> 1))
#    endif
#  endif
#endif

#ifndef PERL_LONG_MIN
#  ifdef LONG_MIN
#    define PERL_LONG_MIN ((long)LONG_MIN)
#  else
#    ifdef MINLONG
#      define PERL_LONG_MIN ((long)MINLONG)
#    else
#      define PERL_LONG_MIN (-PERL_LONG_MAX - ((3 & -1) == 3))
#    endif
#  endif
#endif

#if defined(HAS_QUAD) && (defined(convex) || defined(uts))
#  ifndef PERL_UQUAD_MAX
#    ifdef ULONGLONG_MAX
#      define PERL_UQUAD_MAX ((unsigned long long)ULONGLONG_MAX)
#    else
#      ifdef MAXULONGLONG
#        define PERL_UQUAD_MAX ((unsigned long long)MAXULONGLONG)
#      else
#        define PERL_UQUAD_MAX (~(unsigned long long)0)
#      endif
#    endif
#  endif

#  ifndef PERL_UQUAD_MIN
#    define PERL_UQUAD_MIN ((unsigned long long)0L)
#  endif

#  ifndef PERL_QUAD_MAX
#    ifdef LONGLONG_MAX
#      define PERL_QUAD_MAX ((long long)LONGLONG_MAX)
#    else
#      ifdef MAXLONGLONG
#        define PERL_QUAD_MAX ((long long)MAXLONGLONG)
#      else
#        define PERL_QUAD_MAX ((long long) (PERL_UQUAD_MAX >> 1))
#      endif
#    endif
#  endif

#  ifndef PERL_QUAD_MIN
#    ifdef LONGLONG_MIN
#      define PERL_QUAD_MIN ((long long)LONGLONG_MIN)
#    else
#      ifdef MINLONGLONG
#        define PERL_QUAD_MIN ((long long)MINLONGLONG)
#      else
#        define PERL_QUAD_MIN (-PERL_QUAD_MAX - ((3 & -1) == 3))
#      endif
#    endif
#  endif
#endif

/* This is based on code from 5.003 perl.h */
#ifdef HAS_QUAD
#  ifdef cray
#ifndef IVTYPE
#  define IVTYPE                         int
#endif

#ifndef IV_MIN
#  define IV_MIN                         PERL_INT_MIN
#endif

#ifndef IV_MAX
#  define IV_MAX                         PERL_INT_MAX
#endif

#ifndef UV_MIN
#  define UV_MIN                         PERL_UINT_MIN
#endif

#ifndef UV_MAX
#  define UV_MAX                         PERL_UINT_MAX
#endif

#    ifdef INTSIZE
#ifndef IVSIZE
#  define IVSIZE                         INTSIZE
#endif

#    endif
#  else
#    if defined(convex) || defined(uts)
#ifndef IVTYPE
#  define IVTYPE                         long long
#endif

#ifndef IV_MIN
#  define IV_MIN                         PERL_QUAD_MIN
#endif

#ifndef IV_MAX
#  define IV_MAX                         PERL_QUAD_MAX
#endif

#ifndef UV_MIN
#  define UV_MIN                         PERL_UQUAD_MIN
#endif

#ifndef UV_MAX
#  define UV_MAX                         PERL_UQUAD_MAX
#endif

#      ifdef LONGLONGSIZE
#ifndef IVSIZE
#  define IVSIZE                         LONGLONGSIZE
#endif

#      endif
#    else
#ifndef IVTYPE
#  define IVTYPE                         long
#endif

#ifndef IV_MIN
#  define IV_MIN                         PERL_LONG_MIN
#endif

#ifndef IV_MAX
#  define IV_MAX                         PERL_LONG_MAX
#endif

#ifndef UV_MIN
#  define UV_MIN                         PERL_ULONG_MIN
#endif

#ifndef UV_MAX
#  define UV_MAX                         PERL_ULONG_MAX
#endif

#      ifdef LONGSIZE
#ifndef IVSIZE
#  define IVSIZE                         LONGSIZE
#endif

#      endif
#    endif
#  endif
#ifndef IVSIZE
#  define IVSIZE                         8
#endif

#ifndef PERL_QUAD_MIN
#  define PERL_QUAD_MIN                  IV_MIN
#endif

#ifndef PERL_QUAD_MAX
#  define PERL_QUAD_MAX                  IV_MAX
#endif

#ifndef PERL_UQUAD_MIN
#  define PERL_UQUAD_MIN                 UV_MIN
#endif

#ifndef PERL_UQUAD_MAX
#  define PERL_UQUAD_MAX                 UV_MAX
#endif

#else
#ifndef IVTYPE
#  define IVTYPE                         long
#endif

#ifndef IV_MIN
#  define IV_MIN                         PERL_LONG_MIN
#endif

#ifndef IV_MAX
#  define IV_MAX                         PERL_LONG_MAX
#endif

#ifndef UV_MIN
#  define UV_MIN                         PERL_ULONG_MIN
#endif

#ifndef UV_MAX
#  define UV_MAX                         PERL_ULONG_MAX
#endif

#endif

#ifndef IVSIZE
#  ifdef LONGSIZE
#    define IVSIZE LONGSIZE
#  else
#    define IVSIZE 4 /* A bold guess, but the best we can make. */
#  endif
#endif
#ifndef UVTYPE
#  define UVTYPE                         unsigned IVTYPE
#endif

#ifndef UVSIZE
#  define UVSIZE                         IVSIZE
#endif
#ifndef sv_setuv
#  define sv_setuv(sv, uv)               \
               STMT_START {                         \
                 UV TeMpUv = uv;                    \
                 if (TeMpUv <= IV_MAX)              \
                   sv_setiv(sv, TeMpUv);            \
                 else                               \
                   sv_setnv(sv, (double)TeMpUv);    \
               } STMT_END
#endif
#ifndef newSVuv
#  define newSVuv(uv)                    ((uv) <= IV_MAX ? newSViv((IV)uv) : newSVnv((NV)uv))
#endif
#ifndef sv_2uv
#  define sv_2uv(sv)                     ((PL_Sv = (sv)), (UV) (SvNOK(PL_Sv) ? SvNV(PL_Sv) : sv_2nv(PL_Sv)))
#endif

#ifndef SvUVX
#  define SvUVX(sv)                      ((UV)SvIVX(sv))
#endif

#ifndef SvUVXx
#  define SvUVXx(sv)                     SvUVX(sv)
#endif

#ifndef SvUV
#  define SvUV(sv)                       (SvIOK(sv) ? SvUVX(sv) : sv_2uv(sv))
#endif

#ifndef SvUVx
#  define SvUVx(sv)                      ((PL_Sv = (sv)), SvUV(PL_Sv))
#endif

/* Hint: sv_uv
 * Always use the SvUVx() macro instead of sv_uv().
 */
#ifndef sv_uv
#  define sv_uv(sv)                      SvUVx(sv)
#endif

#if !defined(SvUOK) && defined(SvIOK_UV)
#  define SvUOK(sv) SvIOK_UV(sv)
#endif
#ifndef XST_mUV
#  define XST_mUV(i,v)                   (ST(i) = sv_2mortal(newSVuv(v))  )
#endif

#ifndef XSRETURN_UV
#  define XSRETURN_UV(v)                 STMT_START { XST_mUV(0,v);  XSRETURN(1); } STMT_END
#endif
#ifndef PUSHu
#  define PUSHu(u)                       STMT_START { sv_setuv(TARG, (UV)(u)); PUSHTARG;  } STMT_END
#endif

#ifndef XPUSHu
#  define XPUSHu(u)                      STMT_START { sv_setuv(TARG, (UV)(u)); XPUSHTARG; } STMT_END
#endif

#ifdef HAS_MEMCMP
#ifndef memNE
#  define memNE(s1,s2,l)                 (memcmp(s1,s2,l))
#endif

#ifndef memEQ
#  define memEQ(s1,s2,l)                 (!memcmp(s1,s2,l))
#endif

#else
#ifndef memNE
#  define memNE(s1,s2,l)                 (bcmp(s1,s2,l))
#endif

#ifndef memEQ
#  define memEQ(s1,s2,l)                 (!bcmp(s1,s2,l))
#endif

#endif
#ifndef MoveD
#  define MoveD(s,d,n,t)                 memmove((char*)(d),(char*)(s), (n) * sizeof(t))
#endif

#ifndef CopyD
#  define CopyD(s,d,n,t)                 memcpy((char*)(d),(char*)(s), (n) * sizeof(t))
#endif

#ifdef HAS_MEMSET
#ifndef ZeroD
#  define ZeroD(d,n,t)                   memzero((char*)(d), (n) * sizeof(t))
#endif

#else
#ifndef ZeroD
#  define ZeroD(d,n,t)                   ((void)memzero((char*)(d), (n) * sizeof(t)), d)
#endif

#endif
#ifndef PoisonWith
#  define PoisonWith(d,n,t,b)            (void)memset((char*)(d), (U8)(b), (n) * sizeof(t))
#endif

#ifndef PoisonNew
#  define PoisonNew(d,n,t)               PoisonWith(d,n,t,0xAB)
#endif

#ifndef PoisonFree
#  define PoisonFree(d,n,t)              PoisonWith(d,n,t,0xEF)
#endif

#ifndef Poison
#  define Poison(d,n,t)                  PoisonFree(d,n,t)
#endif
#ifndef Newx
#  define Newx(v,n,t)                    new(0,v,n,t)
#endif

#ifndef Newxc
#  define Newxc(v,n,t,c)                 Newc(0,v,n,t,c)
#endif

#ifndef Newxz
#  define Newxz(v,n,t)                   Newz(0,v,n,t)
#endif

#ifndef PERL_UNUSED_DECL
#  ifdef HASATTRIBUTE
#    if (defined(__GNUC__) && defined(__cplusplus)) || defined(__INTEL_COMPILER)
#      define PERL_UNUSED_DECL
#    else
#      define PERL_UNUSED_DECL __attribute__((unused))
#    endif
#  else
#    define PERL_UNUSED_DECL
#  endif
#endif

#ifndef PERL_UNUSED_ARG
#  if defined(lint) && defined(S_SPLINT_S) /* www.splint.org */
#    include <note.h>
#    define PERL_UNUSED_ARG(x) NOTE(ARGUNUSED(x))
#  else
#    define PERL_UNUSED_ARG(x) ((void)x)
#  endif
#endif

#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(x) ((void)x)
#endif

#ifndef PERL_UNUSED_CONTEXT
#  ifdef USE_ITHREADS
#    define PERL_UNUSED_CONTEXT PERL_UNUSED_ARG(my_perl)
#  else
#    define PERL_UNUSED_CONTEXT
#  endif
#endif
#ifndef NOOP
#  define NOOP                           /*EMPTY*/(void)0
#endif

#ifndef dNOOP
#  define dNOOP                          extern int /*@unused@*/ Perl___notused PERL_UNUSED_DECL
#endif

#ifndef NVTYPE
#  if defined(USE_LONG_DOUBLE) && defined(HAS_LONG_DOUBLE)
#    define NVTYPE long double
#  else
#    define NVTYPE double
#  endif
typedef NVTYPE NV;
#endif

#ifndef INT2PTR
#  if (IVSIZE == PTRSIZE) && (UVSIZE == PTRSIZE)
#    define PTRV                  UV
#    define INT2PTR(any,d)        (any)(d)
#  else
#    if PTRSIZE == LONGSIZE
#      define PTRV                unsigned long
#    else
#      define PTRV                unsigned
#    endif
#    define INT2PTR(any,d)        (any)(PTRV)(d)
#  endif
#endif

#ifndef PTR2ul
#  if PTRSIZE == LONGSIZE
#    define PTR2ul(p)     (unsigned long)(p)
#  else
#    define PTR2ul(p)     INT2PTR(unsigned long,p)
#  endif
#endif
#ifndef PTR2nat
#  define PTR2nat(p)                     (PTRV)(p)
#endif

#ifndef NUM2PTR
#  define NUM2PTR(any,d)                 (any)PTR2nat(d)
#endif

#ifndef PTR2IV
#  define PTR2IV(p)                      INT2PTR(IV,p)
#endif

#ifndef PTR2UV
#  define PTR2UV(p)                      INT2PTR(UV,p)
#endif

#ifndef PTR2NV
#  define PTR2NV(p)                      NUM2PTR(NV,p)
#endif

#undef START_EXTERN_C
#undef END_EXTERN_C
#undef EXTERN_C
#ifdef __cplusplus
#  define START_EXTERN_C extern "C" {
#  define END_EXTERN_C }
#  define EXTERN_C extern "C"
#else
#  define START_EXTERN_C
#  define END_EXTERN_C
#  define EXTERN_C extern
#endif

#if defined(PERL_GCC_PEDANTIC)
#  ifndef PERL_GCC_BRACE_GROUPS_FORBIDDEN
#    define PERL_GCC_BRACE_GROUPS_FORBIDDEN
#  endif
#endif

#if defined(__GNUC__) && !defined(PERL_GCC_BRACE_GROUPS_FORBIDDEN) && !defined(__cplusplus)
#  ifndef PERL_USE_GCC_BRACE_GROUPS
#    define PERL_USE_GCC_BRACE_GROUPS
#  endif
#endif

#undef STMT_START
#undef STMT_END
#ifdef PERL_USE_GCC_BRACE_GROUPS
#  define STMT_START	(void)(	/* gcc supports ``({ STATEMENTS; })'' */
#  define STMT_END	)
#else
#  if defined(VOIDFLAGS) && (VOIDFLAGS) && (defined(sun) || defined(__sun__)) && !defined(__GNUC__)
#    define STMT_START	if (1)
#    define STMT_END	else (void)0
#  else
#    define STMT_START	do
#    define STMT_END	while (0)
#  endif
#endif
#ifndef boolSV
#  define boolSV(b)                      ((b) ? &PL_sv_yes : &PL_sv_no)
#endif

/* DEFSV appears first in 5.004_56 */
#ifndef DEFSV
#  define DEFSV                          GvSV(PL_defgv)
#endif

#ifndef SAVE_DEFSV
#  define SAVE_DEFSV                     SAVESPTR(GvSV(PL_defgv))
#endif

#ifndef DEFSV_set
#  define DEFSV_set(sv)                  (DEFSV = (sv))
#endif

/* Older perls (<=5.003) lack AvFILLp */
#ifndef AvFILLp
#  define AvFILLp                        AvFILL
#endif
#ifndef ERRSV
#  define ERRSV                          get_sv("@",FALSE)
#endif

/* Hint: gv_stashpvn
 * This function's backport doesn't support the length parameter, but
 * rather ignores it. Portability can only be ensured if the length
 * parameter is used for speed reasons, but the length can always be
 * correctly computed from the string argument.
 */
#ifndef gv_stashpvn
#  define gv_stashpvn(str,len,create)    gv_stashpv(str,create)
#endif

/* Replace: 1 */
#ifndef get_cv
#  define get_cv                         perl_get_cv
#endif

#ifndef get_sv
#  define get_sv                         perl_get_sv
#endif

#ifndef get_av
#  define get_av                         perl_get_av
#endif

#ifndef get_hv
#  define get_hv                         perl_get_hv
#endif

/* Replace: 0 */
#ifndef dUNDERBAR
#  define dUNDERBAR                      dNOOP
#endif

#ifndef UNDERBAR
#  define UNDERBAR                       DEFSV
#endif
#ifndef dAX
#  define dAX                            I32 ax = MARK - PL_stack_base + 1
#endif

#ifndef dITEMS
#  define dITEMS                         I32 items = SP - MARK
#endif
#ifndef dXSTARG
#  define dXSTARG                        SV * targ = sv_newmortal()
#endif
#ifndef dAXMARK
#  define dAXMARK                        I32 ax = POPMARK; \
                               register SV ** const mark = PL_stack_base + ax++
#endif
#ifndef XSprePUSH
#  define XSprePUSH                      (sp = PL_stack_base + ax - 1)
#endif

#if (PERL_BCDVERSION < 0x5005000)
#  undef XSRETURN
#  define XSRETURN(off)                                   \
      STMT_START {                                        \
          PL_stack_sp = PL_stack_base + ax + ((off) - 1); \
          return;                                         \
      } STMT_END
#endif
#ifndef XSPROTO
#  define XSPROTO(name)                  void name(pTHX_ CV* cv)
#endif

#ifndef SVfARG
#  define SVfARG(p)                      ((void*)(p))
#endif
#ifndef PERL_ABS
#  define PERL_ABS(x)                    ((x) < 0 ? -(x) : (x))
#endif
#ifndef dVAR
#  define dVAR                           dNOOP
#endif
#ifndef SVf
#  define SVf                            "_"
#endif
#ifndef UTF8_MAXBYTES
#  define UTF8_MAXBYTES                  UTF8_MAXLEN
#endif
#ifndef CPERLscope
#  define CPERLscope(x)                  x
#endif
#ifndef PERL_HASH
#  define PERL_HASH(hash,str,len)        \
     STMT_START	{ \
	const char *s_PeRlHaSh = str; \
	I32 i_PeRlHaSh = len; \
	U32 hash_PeRlHaSh = 0; \
	while (i_PeRlHaSh--) \
	    hash_PeRlHaSh = hash_PeRlHaSh * 33 + *s_PeRlHaSh++; \
	(hash) = hash_PeRlHaSh; \
    } STMT_END
#endif

#ifndef PERLIO_FUNCS_DECL
# ifdef PERLIO_FUNCS_CONST
#  define PERLIO_FUNCS_DECL(funcs) const PerlIO_funcs funcs
#  define PERLIO_FUNCS_CAST(funcs) (PerlIO_funcs*)(funcs)
# else
#  define PERLIO_FUNCS_DECL(funcs) PerlIO_funcs funcs
#  define PERLIO_FUNCS_CAST(funcs) (funcs)
# endif
#endif

/* provide these typedefs for older perls */
#if (PERL_BCDVERSION < 0x5009003)

# ifdef ARGSproto
typedef OP* (CPERLscope(*Perl_ppaddr_t))(ARGSproto);
# else
typedef OP* (CPERLscope(*Perl_ppaddr_t))(pTHX);
# endif

typedef OP* (CPERLscope(*Perl_check_t)) (pTHX_ OP*);

#endif
#ifndef isPSXSPC
#  define isPSXSPC(c)                    (isSPACE(c) || (c) == '\v')
#endif

#ifndef isBLANK
#  define isBLANK(c)                     ((c) == ' ' || (c) == '\t')
#endif

#ifdef EBCDIC
#ifndef isALNUMC
#  define isALNUMC(c)                    isalnum(c)
#endif

#ifndef isASCII
#  define isASCII(c)                     isascii(c)
#endif

#ifndef isCNTRL
#  define isCNTRL(c)                     iscntrl(c)
#endif

#ifndef isGRAPH
#  define isGRAPH(c)                     isgraph(c)
#endif

#ifndef isPRINT
#  define isPRINT(c)                     isprint(c)
#endif

#ifndef isPUNCT
#  define isPUNCT(c)                     ispunct(c)
#endif

#ifndef isXDIGIT
#  define isXDIGIT(c)                    isxdigit(c)
#endif

#else
# if (PERL_BCDVERSION < 0x5010000)
/* Hint: isPRINT
 * The implementation in older perl versions includes all of the
 * isSPACE() characters, which is wrong. The version provided by
 * Devel::PPPort always overrides a present buggy version.
 */
#  undef isPRINT
# endif
#ifndef isALNUMC
#  define isALNUMC(c)                    (isALPHA(c) || isDIGIT(c))
#endif

#ifndef isASCII
#  define isASCII(c)                     ((c) <= 127)
#endif

#ifndef isCNTRL
#  define isCNTRL(c)                     ((c) < ' ' || (c) == 127)
#endif

#ifndef isGRAPH
#  define isGRAPH(c)                     (isALNUM(c) || isPUNCT(c))
#endif

#ifndef isPRINT
#  define isPRINT(c)                     (((c) >= 32 && (c) < 127))
#endif

#ifndef isPUNCT
#  define isPUNCT(c)                     (((c) >= 33 && (c) <= 47) || ((c) >= 58 && (c) <= 64)  || ((c) >= 91 && (c) <= 96) || ((c) >= 123 && (c) <= 126))
#endif

#ifndef isXDIGIT
#  define isXDIGIT(c)                    (isDIGIT(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#endif

#endif

#ifndef PERL_SIGNALS_UNSAFE_FLAG

#define PERL_SIGNALS_UNSAFE_FLAG 0x0001

#if (PERL_BCDVERSION < 0x5008000)
#  define D_PPP_PERL_SIGNALS_INIT   PERL_SIGNALS_UNSAFE_FLAG
#else
#  define D_PPP_PERL_SIGNALS_INIT   0
#endif

#if defined(NEED_PL_signals)
static U32 DPPP_(my_PL_signals) = D_PPP_PERL_SIGNALS_INIT;
#elif defined(NEED_PL_signals_GLOBAL)
U32 DPPP_(my_PL_signals) = D_PPP_PERL_SIGNALS_INIT;
#else
extern U32 DPPP_(my_PL_signals);
#endif
#define PL_signals DPPP_(my_PL_signals)

#endif

/* Hint: PL_ppaddr
 * Calling an op via PL_ppaddr requires passing a context argument
 * for threaded builds. Since the context argument is different for
 * 5.005 perls, you can use aTHXR (supplied by ppport.h), which will
 * automatically be defined as the correct argument.
 */

#if (PERL_BCDVERSION <= 0x5005005)
/* Replace: 1 */
#  define PL_ppaddr                 ppaddr
#  define PL_no_modify              no_modify
/* Replace: 0 */
#endif

#if (PERL_BCDVERSION <= 0x5004005)
/* Replace: 1 */
#  define PL_DBsignal               DBsignal
#  define PL_DBsingle               DBsingle
#  define PL_DBsub                  DBsub
#  define PL_DBtrace                DBtrace
#  define PL_Sv                     Sv
#  define PL_bufend                 bufend
#  define PL_bufptr                 bufptr
#  define PL_compiling              compiling
#  define PL_copline                copline
#  define PL_curcop                 curcop
#  define PL_curstash               curstash
#  define PL_debstash               debstash
#  define PL_defgv                  defgv
#  define PL_diehook                diehook
#  define PL_dirty                  dirty
#  define PL_dowarn                 dowarn
#  define PL_errgv                  errgv
#  define PL_error_count            error_count
#  define PL_expect                 expect
#  define PL_hexdigit               hexdigit
#  define PL_hints                  hints
#  define PL_in_my                  in_my
#  define PL_laststatval            laststatval
#  define PL_lex_state              lex_state
#  define PL_lex_stuff              lex_stuff
#  define PL_linestr                linestr
#  define PL_na                     na
#  define PL_perl_destruct_level    perl_destruct_level
#  define PL_perldb                 perldb
#  define PL_rsfp_filters           rsfp_filters
#  define PL_rsfp                   rsfp
#  define PL_stack_base             stack_base
#  define PL_stack_sp               stack_sp
#  define PL_statcache              statcache
#  define PL_stdingv                stdingv
#  define PL_sv_arenaroot           sv_arenaroot
#  define PL_sv_no                  sv_no
#  define PL_sv_undef               sv_undef
#  define PL_sv_yes                 sv_yes
#  define PL_tainted                tainted
#  define PL_tainting               tainting
#  define PL_tokenbuf               tokenbuf
/* Replace: 0 */
#endif

/* Warning: PL_parser
 * For perl versions earlier than 5.9.5, this__ is an always
 * non-NULL dummy. Also, it cannot be dereferenced. Don't
 * use it if you can avoid is and unless you absolutely know
 * what you're doing.
 * If you always check that PL_parser is non-NULL, you can
 * define DPPP_PL_parser_NO_DUMMY to avoid the creation of
 * a dummy parser structure.
 */

#if (PERL_BCDVERSION >= 0x5009005)
# ifdef DPPP_PL_parser_NO_DUMMY
#  define D_PPP_my_PL_parser_var(var) ((PL_parser ? PL_parser : \
                (croak("panic: PL_parser == NULL in %s:%d", \
                       __FILE__, __LINE__), (yy_parser *) NULL))->var)
# else
#  ifdef DPPP_PL_parser_NO_DUMMY_WARNING
#   define D_PPP_parser_dummy_warning(var)
#  else
#   define D_PPP_parser_dummy_warning(var) \
             warn("warning: dummy PL_" #var " used in %s:%d", __FILE__, __LINE__),
#  endif
#  define D_PPP_my_PL_parser_var(var) ((PL_parser ? PL_parser : \
                (D_PPP_parser_dummy_warning(var) &DPPP_(dummy_PL_parser)))->var)
#if defined(NEED_PL_parser)
static yy_parser DPPP_(dummy_PL_parser);
#elif defined(NEED_PL_parser_GLOBAL)
yy_parser DPPP_(dummy_PL_parser);
#else
extern yy_parser DPPP_(dummy_PL_parser);
#endif

# endif

/* PL_expect, PL_copline, PL_rsfp, PL_rsfp_filters, PL_linestr, PL_bufptr, PL_bufend, PL_lex_state, PL_lex_stuff, PL_tokenbuf depends on PL_parser */
/* Warning: PL_expect, PL_copline, PL_rsfp, PL_rsfp_filters, PL_linestr, PL_bufptr, PL_bufend, PL_lex_state, PL_lex_stuff, PL_tokenbuf
 * Do not use this__ variable unless you know exactly what you're
 * doint. It is internal to the perl parser and may change or even
 * be removed in the future. As of perl 5.9.5, you have to check
 * for (PL_parser != NULL) for this__ variable to have any effect.
 * An always non-NULL PL_parser dummy is provided for earlier
 * perl versions.
 * If PL_parser is NULL when you try to access this__ variable, a
 * dummy is being accessed instead and a warning is issued unless
 * you define DPPP_PL_parser_NO_DUMMY_WARNING.
 * If DPPP_PL_parser_NO_DUMMY is defined, the code trying to access
 * this__ variable will croak with a panic message.
 */

# define PL_expect         D_PPP_my_PL_parser_var(expect)
# define PL_copline        D_PPP_my_PL_parser_var(copline)
# define PL_rsfp           D_PPP_my_PL_parser_var(rsfp)
# define PL_rsfp_filters   D_PPP_my_PL_parser_var(rsfp_filters)
# define PL_linestr        D_PPP_my_PL_parser_var(linestr)
# define PL_bufptr         D_PPP_my_PL_parser_var(bufptr)
# define PL_bufend         D_PPP_my_PL_parser_var(bufend)
# define PL_lex_state      D_PPP_my_PL_parser_var(lex_state)
# define PL_lex_stuff      D_PPP_my_PL_parser_var(lex_stuff)
# define PL_tokenbuf       D_PPP_my_PL_parser_var(tokenbuf)
# define PL_in_my          D_PPP_my_PL_parser_var(in_my)
# define PL_in_my_stash    D_PPP_my_PL_parser_var(in_my_stash)
# define PL_error_count    D_PPP_my_PL_parser_var(error_count)


#else

/* ensure that PL_parser != NULL and cannot be dereferenced */
# define PL_parser         ((void *) 1)

#endif
#ifndef mPUSHs
#  define mPUSHs(s)                      PUSHs(sv_2mortal(s))
#endif

#ifndef PUSHmortal
#  define PUSHmortal                     PUSHs(sv_newmortal())
#endif

#ifndef mPUSHp
#  define mPUSHp(p,l)                    sv_setpvn(PUSHmortal, (p), (l))
#endif

#ifndef mPUSHn
#  define mPUSHn(n)                      sv_setnv(PUSHmortal, (NV)(n))
#endif

#ifndef mPUSHi
#  define mPUSHi(i)                      sv_setiv(PUSHmortal, (IV)(i))
#endif

#ifndef mPUSHu
#  define mPUSHu(u)                      sv_setuv(PUSHmortal, (UV)(u))
#endif
#ifndef mXPUSHs
#  define mXPUSHs(s)                     XPUSHs(sv_2mortal(s))
#endif

#ifndef XPUSHmortal
#  define XPUSHmortal                    XPUSHs(sv_newmortal())
#endif

#ifndef mXPUSHp
#  define mXPUSHp(p,l)                   STMT_START { EXTEND(sp,1); sv_setpvn(PUSHmortal, (p), (l)); } STMT_END
#endif

#ifndef mXPUSHn
#  define mXPUSHn(n)                     STMT_START { EXTEND(sp,1); sv_setnv(PUSHmortal, (NV)(n)); } STMT_END
#endif

#ifndef mXPUSHi
#  define mXPUSHi(i)                     STMT_START { EXTEND(sp,1); sv_setiv(PUSHmortal, (IV)(i)); } STMT_END
#endif

#ifndef mXPUSHu
#  define mXPUSHu(u)                     STMT_START { EXTEND(sp,1); sv_setuv(PUSHmortal, (UV)(u)); } STMT_END
#endif

/* Replace: 1 */
#ifndef call_sv
#  define call_sv                        perl_call_sv
#endif

#ifndef call_pv
#  define call_pv                        perl_call_pv
#endif

#ifndef call_argv
#  define call_argv                      perl_call_argv
#endif

#ifndef call_method
#  define call_method                    perl_call_method
#endif
#ifndef eval_sv
#  define eval_sv                        perl_eval_sv
#endif

/* Replace: 0 */
#ifndef PERL_LOADMOD_DENY
#  define PERL_LOADMOD_DENY              0x1
#endif

#ifndef PERL_LOADMOD_NOIMPORT
#  define PERL_LOADMOD_NOIMPORT          0x2
#endif

#ifndef PERL_LOADMOD_IMPORT_OPS
#  define PERL_LOADMOD_IMPORT_OPS        0x4
#endif

#ifndef G_METHOD
# define G_METHOD		64
# ifdef call_sv
#  undef call_sv
# endif
# if (PERL_BCDVERSION < 0x5006000)
#  define call_sv(sv, flags)  ((flags) & G_METHOD ? perl_call_method((char *) SvPV_nolen_const(sv), \
				(flags) & ~G_METHOD) : perl_call_sv(sv, flags))
# else
#  define call_sv(sv, flags)  ((flags) & G_METHOD ? Perl_call_method(aTHX_ (char *) SvPV_nolen_const(sv), \
				(flags) & ~G_METHOD) : Perl_call_sv(aTHX_ sv, flags))
# endif
#endif

/* Replace perl_eval_pv with eval_pv */

#ifndef eval_pv
#if defined(NEED_eval_pv)
static SV* DPPP_(my_eval_pv)(char *p, I32 croak_on_error);
static
#else
extern SV* DPPP_(my_eval_pv)(char *p, I32 croak_on_error);
#endif

#ifdef eval_pv
#  undef eval_pv
#endif
#define eval_pv(a,b) DPPP_(my_eval_pv)(aTHX_ a,b)
#define Perl_eval_pv DPPP_(my_eval_pv)

#if defined(NEED_eval_pv) || defined(NEED_eval_pv_GLOBAL)

SV*
DPPP_(my_eval_pv)(char *p, I32 croak_on_error)
{
    dSP;
    SV* sv = newSVpv(p, 0);

    PUSHMARK(sp);
    eval_sv(sv, G_SCALAR);
    SvREFCNT_dec(sv);

    SPAGAIN;
    sv = POPs;
    PUTBACK;

    if (croak_on_error && SvTRUE(GvSV(errgv)))
	croak(SvPVx(GvSV(errgv), na));

    return sv;
}

#endif
#endif

#ifndef vload_module
#if defined(NEED_vload_module)
static void DPPP_(my_vload_module)(U32 flags, SV *name, SV *ver, va_list *args);
static
#else
extern void DPPP_(my_vload_module)(U32 flags, SV *name, SV *ver, va_list *args);
#endif

#ifdef vload_module
#  undef vload_module
#endif
#define vload_module(a,b,c,d) DPPP_(my_vload_module)(aTHX_ a,b,c,d)
#define Perl_vload_module DPPP_(my_vload_module)

#if defined(NEED_vload_module) || defined(NEED_vload_module_GLOBAL)

void
DPPP_(my_vload_module)(U32 flags, SV *name, SV *ver, va_list *args)
{
    dTHR;
    dVAR;
    OP *veop, *imop;

    OP * const modname = newSVOP(OP_CONST, 0, name);
    /* 5.005 has a somewhat hacky force_normal that doesn't croak on
       SvREADONLY() if PL_compling is true. Current perls take care in
       ck_require() to correctly turn off SvREADONLY before calling
       force_normal_flags(). This seems a better fix than fudging PL_compling
     */
    SvREADONLY_off(((SVOP*)modname)->op_sv);
    modname->op_private |= OPpCONST_BARE;
    if (ver) {
	veop = newSVOP(OP_CONST, 0, ver);
    }
    else
	veop = NULL;
    if (flags & PERL_LOADMOD_NOIMPORT) {
	imop = sawparens(newNULLLIST());
    }
    else if (flags & PERL_LOADMOD_IMPORT_OPS) {
	imop = va_arg(*args, OP*);
    }
    else {
	SV *sv;
	imop = NULL;
	sv = va_arg(*args, SV*);
	while (sv) {
	    imop = append_elem(OP_LIST, imop, newSVOP(OP_CONST, 0, sv));
	    sv = va_arg(*args, SV*);
	}
    }
    {
	const line_t ocopline = PL_copline;
	COP * const ocurcop = PL_curcop;
	const int oexpect = PL_expect;

#if (PERL_BCDVERSION >= 0x5004000)
	utilize(!(flags & PERL_LOADMOD_DENY), start_subparse(FALSE, 0),
		veop, modname, imop);
#else
	utilize(!(flags & PERL_LOADMOD_DENY), start_subparse(),
		modname, imop);
#endif
	PL_expect = oexpect;
	PL_copline = ocopline;
	PL_curcop = ocurcop;
    }
}

#endif
#endif

#ifndef load_module
#if defined(NEED_load_module)
static void DPPP_(my_load_module)(U32 flags, SV *name, SV *ver, ...);
static
#else
extern void DPPP_(my_load_module)(U32 flags, SV *name, SV *ver, ...);
#endif

#ifdef load_module
#  undef load_module
#endif
#define load_module DPPP_(my_load_module)
#define Perl_load_module DPPP_(my_load_module)

#if defined(NEED_load_module) || defined(NEED_load_module_GLOBAL)

void
DPPP_(my_load_module)(U32 flags, SV *name, SV *ver, ...)
{
    va_list args;
    va_start(args, ver);
    vload_module(flags, name, ver, &args);
    va_end(args);
}

#endif
#endif
#ifndef newRV_inc
#  define newRV_inc(sv)                  newRV(sv)   /* Replace */
#endif

#ifndef newRV_noinc
#if defined(NEED_newRV_noinc)
static SV * DPPP_(my_newRV_noinc)(SV *sv);
static
#else
extern SV * DPPP_(my_newRV_noinc)(SV *sv);
#endif

#ifdef newRV_noinc
#  undef newRV_noinc
#endif
#define newRV_noinc(a) DPPP_(my_newRV_noinc)(aTHX_ a)
#define Perl_newRV_noinc DPPP_(my_newRV_noinc)

#if defined(NEED_newRV_noinc) || defined(NEED_newRV_noinc_GLOBAL)
SV *
DPPP_(my_newRV_noinc)(SV *sv)
{
  SV *rv = (SV *)newRV(sv);
  SvREFCNT_dec(sv);
  return rv;
}
#endif
#endif

/* Hint: newCONSTSUB
 * Returns a CV* as of perl-5.7.1. This return value is not supported
 * by Devel::PPPort.
 */

/* newCONSTSUB from IO.xs is in the core starting with 5.004_63 */
#if (PERL_BCDVERSION < 0x5004063) && (PERL_BCDVERSION != 0x5004005)
#if defined(NEED_newCONSTSUB)
static void DPPP_(my_newCONSTSUB)(HV *stash, const char *name, SV *sv);
static
#else
extern void DPPP_(my_newCONSTSUB)(HV *stash, const char *name, SV *sv);
#endif

#ifdef newCONSTSUB
#  undef newCONSTSUB
#endif
#define newCONSTSUB(a,b,c) DPPP_(my_newCONSTSUB)(aTHX_ a,b,c)
#define Perl_newCONSTSUB DPPP_(my_newCONSTSUB)

#if defined(NEED_newCONSTSUB) || defined(NEED_newCONSTSUB_GLOBAL)

/* This is just a trick to avoid a dependency of newCONSTSUB on PL_parser */
/* (There's no PL_parser in perl < 5.005, so this__ is completely safe)     */
#define D_PPP_PL_copline PL_copline

void
DPPP_(my_newCONSTSUB)(HV *stash, const char *name, SV *sv)
{
	U32 oldhints = PL_hints;
	HV *old_cop_stash = PL_curcop->cop_stash;
	HV *old_curstash = PL_curstash;
	line_t oldline = PL_curcop->cop_line;
	PL_curcop->cop_line = D_PPP_PL_copline;

	PL_hints &= ~HINT_BLOCK_SCOPE;
	if (stash)
		PL_curstash = PL_curcop->cop_stash = stash;

	newSUB(

#if   (PERL_BCDVERSION < 0x5003022)
		start_subparse(),
#elif (PERL_BCDVERSION == 0x5003022)
     		start_subparse(0),
#else  /* 5.003_23  onwards */
     		start_subparse(FALSE, 0),
#endif

		newSVOP(OP_CONST, 0, newSVpv((char *) name, 0)),
		newSVOP(OP_CONST, 0, &PL_sv_no),   /* SvPV(&PL_sv_no) == "" -- GMB */
		newSTATEOP(0, Nullch, newSVOP(OP_CONST, 0, sv))
	);

	PL_hints = oldhints;
	PL_curcop->cop_stash = old_cop_stash;
	PL_curstash = old_curstash;
	PL_curcop->cop_line = oldline;
}
#endif
#endif

/*
 * Boilerplate macros for initializing and accessing interpreter-local
 * data from C.  All statics in extensions should be reworked to use
 * this__, if you want to make the extension thread-safe.  See ext/re/re.xs
 * for an example of the use of these macros.
 *
 * Code that uses these macros is responsible for the following:
 * 1. #define MY_CXT_KEY to a unique string, e.g. "DynaLoader_guts"
 * 2. Declare a typedef named my_cxt_t that is a structure that contains
 *    all the data that needs to be interpreter-local.
 * 3. Use the START_MY_CXT macro after the declaration of my_cxt_t.
 * 4. Use the MY_CXT_INIT macro such that it is called exactly once
 *    (typically put in the BOOT: section).
 * 5. Use the members of the my_cxt_t structure everywhere as
 *    MY_CXT.member.
 * 6. Use the dMY_CXT macro (a declaration) in all the functions that
 *    access MY_CXT.
 */

#if defined(MULTIPLICITY) || defined(PERL_OBJECT) || \
    defined(PERL_CAPI)    || defined(PERL_IMPLICIT_CONTEXT)

#ifndef START_MY_CXT

/* This must appear in all extensions that define a my_cxt_t structure,
 * right after the definition (i.e. at file scope).  The non-threads
 * case below uses it to declare the data as static. */
#define START_MY_CXT

#if (PERL_BCDVERSION < 0x5004068)
/* Fetches the SV that keeps the per-interpreter data. */
#define dMY_CXT_SV \
	SV *my_cxt_sv = get_sv(MY_CXT_KEY, FALSE)
#else /* >= perl5.004_68 */
#define dMY_CXT_SV \
	SV *my_cxt_sv = *hv_fetch(PL_modglobal, MY_CXT_KEY,		\
				  sizeof(MY_CXT_KEY)-1, TRUE)
#endif /* < perl5.004_68 */

/* This declaration should be used within all functions that use the
 * interpreter-local data. */
#define dMY_CXT	\
	dMY_CXT_SV;							\
	my_cxt_t *my_cxtp = INT2PTR(my_cxt_t*,SvUV(my_cxt_sv))

/* Creates and zeroes the per-interpreter data.
 * (We allocate my_cxtp in a Perl SV so that it will be released when
 * the interpreter goes away.) */
#define MY_CXT_INIT \
	dMY_CXT_SV;							\
	/* newSV() allocates one more than needed */			\
	my_cxt_t *my_cxtp = (my_cxt_t*)SvPVX(newSV(sizeof(my_cxt_t)-1));\
	Zero(my_cxtp, 1, my_cxt_t);					\
	sv_setuv(my_cxt_sv, PTR2UV(my_cxtp))

/* This macro must be used to access members of the my_cxt_t structure.
 * e.g. MYCXT.some_data */
#define MY_CXT		(*my_cxtp)

/* Judicious use of these macros can reduce the number of times dMY_CXT
 * is used.  Use is similar to pTHX, aTHX etc. */
#define pMY_CXT		my_cxt_t *my_cxtp
#define pMY_CXT_	pMY_CXT,
#define _pMY_CXT	,pMY_CXT
#define aMY_CXT		my_cxtp
#define aMY_CXT_	aMY_CXT,
#define _aMY_CXT	,aMY_CXT

#endif /* START_MY_CXT */

#ifndef MY_CXT_CLONE
/* Clones the per-interpreter data. */
#define MY_CXT_CLONE \
	dMY_CXT_SV;							\
	my_cxt_t *my_cxtp = (my_cxt_t*)SvPVX(newSV(sizeof(my_cxt_t)-1));\
	Copy(INT2PTR(my_cxt_t*, SvUV(my_cxt_sv)), my_cxtp, 1, my_cxt_t);\
	sv_setuv(my_cxt_sv, PTR2UV(my_cxtp))
#endif

#else /* single interpreter */

#ifndef START_MY_CXT

#define START_MY_CXT	static my_cxt_t my_cxt;
#define dMY_CXT_SV	dNOOP
#define dMY_CXT		dNOOP
#define MY_CXT_INIT	NOOP
#define MY_CXT		my_cxt

#define pMY_CXT		void
#define pMY_CXT_
#define _pMY_CXT
#define aMY_CXT
#define aMY_CXT_
#define _aMY_CXT

#endif /* START_MY_CXT */

#ifndef MY_CXT_CLONE
#define MY_CXT_CLONE	NOOP
#endif

#endif

#ifndef IVdf
#  if IVSIZE == LONGSIZE
#    define	IVdf      "ld"
#    define	UVuf      "lu"
#    define	UVof      "lo"
#    define	UVxf      "lx"
#    define	UVXf      "lX"
#  else
#    if IVSIZE == INTSIZE
#      define	IVdf      "d"
#      define	UVuf      "u"
#      define	UVof      "o"
#      define	UVxf      "x"
#      define	UVXf      "X"
#    endif
#  endif
#endif

#ifndef NVef
#  if defined(USE_LONG_DOUBLE) && defined(HAS_LONG_DOUBLE) && \
      defined(PERL_PRIfldbl) && (PERL_BCDVERSION != 0x5006000)
            /* Not very likely, but let's try anyway. */
#    define NVef          PERL_PRIeldbl
#    define NVff          PERL_PRIfldbl
#    define NVgf          PERL_PRIgldbl
#  else
#    define NVef          "e"
#    define NVff          "f"
#    define NVgf          "g"
#  endif
#endif

#ifndef SvREFCNT_inc
#  ifdef PERL_USE_GCC_BRACE_GROUPS
#    define SvREFCNT_inc(sv)		\
      ({				\
          SV * const _sv = (SV*)(sv);	\
          if (_sv)			\
               (SvREFCNT(_sv))++;	\
          _sv;				\
      })
#  else
#    define SvREFCNT_inc(sv)	\
          ((PL_Sv=(SV*)(sv)) ? (++(SvREFCNT(PL_Sv)),PL_Sv) : NULL)
#  endif
#endif

#ifndef SvREFCNT_inc_simple
#  ifdef PERL_USE_GCC_BRACE_GROUPS
#    define SvREFCNT_inc_simple(sv)	\
      ({					\
          if (sv)				\
               (SvREFCNT(sv))++;		\
          (SV *)(sv);				\
      })
#  else
#    define SvREFCNT_inc_simple(sv) \
          ((sv) ? (SvREFCNT(sv)++,(SV*)(sv)) : NULL)
#  endif
#endif

#ifndef SvREFCNT_inc_NN
#  ifdef PERL_USE_GCC_BRACE_GROUPS
#    define SvREFCNT_inc_NN(sv)		\
      ({					\
          SV * const _sv = (SV*)(sv);	\
          SvREFCNT(_sv)++;		\
          _sv;				\
      })
#  else
#    define SvREFCNT_inc_NN(sv) \
          (PL_Sv=(SV*)(sv),++(SvREFCNT(PL_Sv)),PL_Sv)
#  endif
#endif

#ifndef SvREFCNT_inc_void
#  ifdef PERL_USE_GCC_BRACE_GROUPS
#    define SvREFCNT_inc_void(sv)		\
      ({					\
          SV * const _sv = (SV*)(sv);	\
          if (_sv)			\
              (void)(SvREFCNT(_sv)++);	\
      })
#  else
#    define SvREFCNT_inc_void(sv) \
          (void)((PL_Sv=(SV*)(sv)) ? ++(SvREFCNT(PL_Sv)) : 0)
#  endif
#endif
#ifndef SvREFCNT_inc_simple_void
#  define SvREFCNT_inc_simple_void(sv)   STMT_START { if (sv) SvREFCNT(sv)++; } STMT_END
#endif

#ifndef SvREFCNT_inc_simple_NN
#  define SvREFCNT_inc_simple_NN(sv)     (++SvREFCNT(sv), (SV*)(sv))
#endif

#ifndef SvREFCNT_inc_void_NN
#  define SvREFCNT_inc_void_NN(sv)       (void)(++SvREFCNT((SV*)(sv)))
#endif

#ifndef SvREFCNT_inc_simple_void_NN
#  define SvREFCNT_inc_simple_void_NN(sv) (void)(++SvREFCNT((SV*)(sv)))
#endif

#ifndef newSV_type

#if defined(NEED_newSV_type)
static SV* DPPP_(my_newSV_type)(pTHX_ svtype const t);
static
#else
extern SV* DPPP_(my_newSV_type)(pTHX_ svtype const t);
#endif

#ifdef newSV_type
#  undef newSV_type
#endif
#define newSV_type(a) DPPP_(my_newSV_type)(aTHX_ a)
#define Perl_newSV_type DPPP_(my_newSV_type)

#if defined(NEED_newSV_type) || defined(NEED_newSV_type_GLOBAL)

SV*
DPPP_(my_newSV_type)(pTHX_ svtype const t)
{
  SV* const sv = newSV(0);
  sv_upgrade(sv, t);
  return sv;
}

#endif

#endif

#if (PERL_BCDVERSION < 0x5006000)
# define D_PPP_CONSTPV_ARG(x)  ((char *) (x))
#else
# define D_PPP_CONSTPV_ARG(x)  (x)
#endif
#ifndef newSVpvn
#  define newSVpvn(data,len)             ((data)                                              \
                                    ? ((len) ? newSVpv((data), (len)) : newSVpv("", 0)) \
                                    : newSV(0))
#endif
#ifndef newSVpvn_utf8
#  define newSVpvn_utf8(s, len, u)       newSVpvn_flags((s), (len), (u) ? SVf_UTF8 : 0)
#endif
#ifndef SVf_UTF8
#  define SVf_UTF8                       0
#endif

#ifndef newSVpvn_flags

#if defined(NEED_newSVpvn_flags)
static SV * DPPP_(my_newSVpvn_flags)(pTHX_ const char *s, STRLEN len, U32 flags);
static
#else
extern SV * DPPP_(my_newSVpvn_flags)(pTHX_ const char *s, STRLEN len, U32 flags);
#endif

#ifdef newSVpvn_flags
#  undef newSVpvn_flags
#endif
#define newSVpvn_flags(a,b,c) DPPP_(my_newSVpvn_flags)(aTHX_ a,b,c)
#define Perl_newSVpvn_flags DPPP_(my_newSVpvn_flags)

#if defined(NEED_newSVpvn_flags) || defined(NEED_newSVpvn_flags_GLOBAL)

SV *
DPPP_(my_newSVpvn_flags)(pTHX_ const char *s, STRLEN len, U32 flags)
{
  SV *sv = newSVpvn(D_PPP_CONSTPV_ARG(s), len);
  SvFLAGS(sv) |= (flags & SVf_UTF8);
  return (flags & SVs_TEMP) ? sv_2mortal(sv) : sv;
}

#endif

#endif

/* Backwards compatibility stuff... :-( */
#if !defined(NEED_sv_2pv_flags) && defined(NEED_sv_2pv_nolen)
#  define NEED_sv_2pv_flags
#endif
#if !defined(NEED_sv_2pv_flags_GLOBAL) && defined(NEED_sv_2pv_nolen_GLOBAL)
#  define NEED_sv_2pv_flags_GLOBAL
#endif

/* Hint: sv_2pv_nolen
 * Use the SvPV_nolen() or SvPV_nolen_const() macros instead of sv_2pv_nolen().
 */
#ifndef sv_2pv_nolen
#  define sv_2pv_nolen(sv)               SvPV_nolen(sv)
#endif

#ifdef SvPVbyte

/* Hint: SvPVbyte
 * Does not work in perl-5.6.1, ppport.h implements a version
 * borrowed from perl-5.7.3.
 */

#if (PERL_BCDVERSION < 0x5007000)

#if defined(NEED_sv_2pvbyte)
static char * DPPP_(my_sv_2pvbyte)(pTHX_ SV *sv, STRLEN *lp);
static
#else
extern char * DPPP_(my_sv_2pvbyte)(pTHX_ SV *sv, STRLEN *lp);
#endif

#ifdef sv_2pvbyte
#  undef sv_2pvbyte
#endif
#define sv_2pvbyte(a,b) DPPP_(my_sv_2pvbyte)(aTHX_ a,b)
#define Perl_sv_2pvbyte DPPP_(my_sv_2pvbyte)

#if defined(NEED_sv_2pvbyte) || defined(NEED_sv_2pvbyte_GLOBAL)

char *
DPPP_(my_sv_2pvbyte)(pTHX_ SV *sv, STRLEN *lp)
{
  sv_utf8_downgrade(sv,0);
  return SvPV(sv,*lp);
}

#endif

/* Hint: sv_2pvbyte
 * Use the SvPVbyte() macro instead of sv_2pvbyte().
 */

#undef SvPVbyte

#define SvPVbyte(sv, lp)                                                \
        ((SvFLAGS(sv) & (SVf_POK|SVf_UTF8)) == (SVf_POK)                \
         ? ((lp = SvCUR(sv)), SvPVX(sv)) : sv_2pvbyte(sv, &lp))

#endif

#else

#  define SvPVbyte          SvPV
#  define sv_2pvbyte        sv_2pv

#endif
#ifndef sv_2pvbyte_nolen
#  define sv_2pvbyte_nolen(sv)           sv_2pv_nolen(sv)
#endif

/* Hint: sv_pvn
 * Always use the SvPV() macro instead of sv_pvn().
 */

/* Hint: sv_pvn_force
 * Always use the SvPV_force() macro instead of sv_pvn_force().
 */

/* If these are undefined, they're not handled by the core anyway */
#ifndef SV_IMMEDIATE_UNREF
#  define SV_IMMEDIATE_UNREF             0
#endif

#ifndef SV_GMAGIC
#  define SV_GMAGIC                      0
#endif

#ifndef SV_COW_DROP_PV
#  define SV_COW_DROP_PV                 0
#endif

#ifndef SV_UTF8_NO_ENCODING
#  define SV_UTF8_NO_ENCODING            0
#endif

#ifndef SV_NOSTEAL
#  define SV_NOSTEAL                     0
#endif

#ifndef SV_CONST_RETURN
#  define SV_CONST_RETURN                0
#endif

#ifndef SV_MUTABLE_RETURN
#  define SV_MUTABLE_RETURN              0
#endif

#ifndef SV_SMAGIC
#  define SV_SMAGIC                      0
#endif

#ifndef SV_HAS_TRAILING_NUL
#  define SV_HAS_TRAILING_NUL            0
#endif

#ifndef SV_COW_SHARED_HASH_KEYS
#  define SV_COW_SHARED_HASH_KEYS        0
#endif

#if (PERL_BCDVERSION < 0x5007002)

#if defined(NEED_sv_2pv_flags)
static char * DPPP_(my_sv_2pv_flags)(pTHX_ SV *sv, STRLEN *lp, I32 flags);
static
#else
extern char * DPPP_(my_sv_2pv_flags)(pTHX_ SV *sv, STRLEN *lp, I32 flags);
#endif

#ifdef sv_2pv_flags
#  undef sv_2pv_flags
#endif
#define sv_2pv_flags(a,b,c) DPPP_(my_sv_2pv_flags)(aTHX_ a,b,c)
#define Perl_sv_2pv_flags DPPP_(my_sv_2pv_flags)

#if defined(NEED_sv_2pv_flags) || defined(NEED_sv_2pv_flags_GLOBAL)

char *
DPPP_(my_sv_2pv_flags)(pTHX_ SV *sv, STRLEN *lp, I32 flags)
{
  STRLEN n_a = (STRLEN) flags;
  return sv_2pv(sv, lp ? lp : &n_a);
}

#endif

#if defined(NEED_sv_pvn_force_flags)
static char * DPPP_(my_sv_pvn_force_flags)(pTHX_ SV *sv, STRLEN *lp, I32 flags);
static
#else
extern char * DPPP_(my_sv_pvn_force_flags)(pTHX_ SV *sv, STRLEN *lp, I32 flags);
#endif

#ifdef sv_pvn_force_flags
#  undef sv_pvn_force_flags
#endif
#define sv_pvn_force_flags(a,b,c) DPPP_(my_sv_pvn_force_flags)(aTHX_ a,b,c)
#define Perl_sv_pvn_force_flags DPPP_(my_sv_pvn_force_flags)

#if defined(NEED_sv_pvn_force_flags) || defined(NEED_sv_pvn_force_flags_GLOBAL)

char *
DPPP_(my_sv_pvn_force_flags)(pTHX_ SV *sv, STRLEN *lp, I32 flags)
{
  STRLEN n_a = (STRLEN) flags;
  return sv_pvn_force(sv, lp ? lp : &n_a);
}

#endif

#endif

#if (PERL_BCDVERSION < 0x5008008) || ( (PERL_BCDVERSION >= 0x5009000) && (PERL_BCDVERSION < 0x5009003) )
# define DPPP_SVPV_NOLEN_LP_ARG &PL_na
#else
# define DPPP_SVPV_NOLEN_LP_ARG 0
#endif
#ifndef SvPV_const
#  define SvPV_const(sv, lp)             SvPV_flags_const(sv, lp, SV_GMAGIC)
#endif

#ifndef SvPV_mutable
#  define SvPV_mutable(sv, lp)           SvPV_flags_mutable(sv, lp, SV_GMAGIC)
#endif
#ifndef SvPV_flags
#  define SvPV_flags(sv, lp, flags)      \
                 ((SvFLAGS(sv) & (SVf_POK)) == SVf_POK \
                  ? ((lp = SvCUR(sv)), SvPVX(sv)) : sv_2pv_flags(sv, &lp, flags))
#endif
#ifndef SvPV_flags_const
#  define SvPV_flags_const(sv, lp, flags) \
                 ((SvFLAGS(sv) & (SVf_POK)) == SVf_POK \
                  ? ((lp = SvCUR(sv)), SvPVX_const(sv)) : \
                  (const char*) sv_2pv_flags(sv, &lp, flags|SV_CONST_RETURN))
#endif
#ifndef SvPV_flags_const_nolen
#  define SvPV_flags_const_nolen(sv, flags) \
                 ((SvFLAGS(sv) & (SVf_POK)) == SVf_POK \
                  ? SvPVX_const(sv) : \
                  (const char*) sv_2pv_flags(sv, DPPP_SVPV_NOLEN_LP_ARG, flags|SV_CONST_RETURN))
#endif
#ifndef SvPV_flags_mutable
#  define SvPV_flags_mutable(sv, lp, flags) \
                 ((SvFLAGS(sv) & (SVf_POK)) == SVf_POK \
                  ? ((lp = SvCUR(sv)), SvPVX_mutable(sv)) : \
                  sv_2pv_flags(sv, &lp, flags|SV_MUTABLE_RETURN))
#endif
#ifndef SvPV_force
#  define SvPV_force(sv, lp)             SvPV_force_flags(sv, lp, SV_GMAGIC)
#endif

#ifndef SvPV_force_nolen
#  define SvPV_force_nolen(sv)           SvPV_force_flags_nolen(sv, SV_GMAGIC)
#endif

#ifndef SvPV_force_mutable
#  define SvPV_force_mutable(sv, lp)     SvPV_force_flags_mutable(sv, lp, SV_GMAGIC)
#endif

#ifndef SvPV_force_nomg
#  define SvPV_force_nomg(sv, lp)        SvPV_force_flags(sv, lp, 0)
#endif

#ifndef SvPV_force_nomg_nolen
#  define SvPV_force_nomg_nolen(sv)      SvPV_force_flags_nolen(sv, 0)
#endif
#ifndef SvPV_force_flags
#  define SvPV_force_flags(sv, lp, flags) \
                 ((SvFLAGS(sv) & (SVf_POK|SVf_THINKFIRST)) == SVf_POK \
                 ? ((lp = SvCUR(sv)), SvPVX(sv)) : sv_pvn_force_flags(sv, &lp, flags))
#endif
#ifndef SvPV_force_flags_nolen
#  define SvPV_force_flags_nolen(sv, flags) \
                 ((SvFLAGS(sv) & (SVf_POK|SVf_THINKFIRST)) == SVf_POK \
                 ? SvPVX(sv) : sv_pvn_force_flags(sv, DPPP_SVPV_NOLEN_LP_ARG, flags))
#endif
#ifndef SvPV_force_flags_mutable
#  define SvPV_force_flags_mutable(sv, lp, flags) \
                 ((SvFLAGS(sv) & (SVf_POK|SVf_THINKFIRST)) == SVf_POK \
                 ? ((lp = SvCUR(sv)), SvPVX_mutable(sv)) \
                  : sv_pvn_force_flags(sv, &lp, flags|SV_MUTABLE_RETURN))
#endif
#ifndef SvPV_nolen
#  define SvPV_nolen(sv)                 \
                 ((SvFLAGS(sv) & (SVf_POK)) == SVf_POK \
                  ? SvPVX(sv) : sv_2pv_flags(sv, DPPP_SVPV_NOLEN_LP_ARG, SV_GMAGIC))
#endif
#ifndef SvPV_nolen_const
#  define SvPV_nolen_const(sv)           \
                 ((SvFLAGS(sv) & (SVf_POK)) == SVf_POK \
                  ? SvPVX_const(sv) : sv_2pv_flags(sv, DPPP_SVPV_NOLEN_LP_ARG, SV_GMAGIC|SV_CONST_RETURN))
#endif
#ifndef SvPV_nomg
#  define SvPV_nomg(sv, lp)              SvPV_flags(sv, lp, 0)
#endif

#ifndef SvPV_nomg_const
#  define SvPV_nomg_const(sv, lp)        SvPV_flags_const(sv, lp, 0)
#endif

#ifndef SvPV_nomg_const_nolen
#  define SvPV_nomg_const_nolen(sv)      SvPV_flags_const_nolen(sv, 0)
#endif
#ifndef SvPV_renew
#  define SvPV_renew(sv,n)               STMT_START { SvLEN_set(sv, n); \
                 SvPV_set((sv), (char *) saferealloc(          \
                       (Malloc_t)SvPVX(sv), (MEM_SIZE)((n)))); \
               } STMT_END
#endif
#ifndef SvMAGIC_set
#  define SvMAGIC_set(sv, val)           \
                STMT_START { assert(SvTYPE(sv) >= SVt_PVMG); \
                (((XPVMG*) SvANY(sv))->xmg_magic = (val)); } STMT_END
#endif

#if (PERL_BCDVERSION < 0x5009003)
#ifndef SvPVX_const
#  define SvPVX_const(sv)                ((const char*) (0 + SvPVX(sv)))
#endif

#ifndef SvPVX_mutable
#  define SvPVX_mutable(sv)              (0 + SvPVX(sv))
#endif
#ifndef SvRV_set
#  define SvRV_set(sv, val)              \
                STMT_START { assert(SvTYPE(sv) >=  SVt_RV); \
                (((XRV*) SvANY(sv))->xrv_rv = (val)); } STMT_END
#endif

#else
#ifndef SvPVX_const
#  define SvPVX_const(sv)                ((const char*)((sv)->sv_u.svu_pv))
#endif

#ifndef SvPVX_mutable
#  define SvPVX_mutable(sv)              ((sv)->sv_u.svu_pv)
#endif
#ifndef SvRV_set
#  define SvRV_set(sv, val)              \
                STMT_START { assert(SvTYPE(sv) >=  SVt_RV); \
                ((sv)->sv_u.svu_rv = (val)); } STMT_END
#endif

#endif
#ifndef SvSTASH_set
#  define SvSTASH_set(sv, val)           \
                STMT_START { assert(SvTYPE(sv) >= SVt_PVMG); \
                (((XPVMG*) SvANY(sv))->xmg_stash = (val)); } STMT_END
#endif

#if (PERL_BCDVERSION < 0x5004000)
#ifndef SvUV_set
#  define SvUV_set(sv, val)              \
                STMT_START { assert(SvTYPE(sv) == SVt_IV || SvTYPE(sv) >= SVt_PVIV); \
                (((XPVIV*) SvANY(sv))->xiv_iv = (IV) (val)); } STMT_END
#endif

#else
#ifndef SvUV_set
#  define SvUV_set(sv, val)              \
                STMT_START { assert(SvTYPE(sv) == SVt_IV || SvTYPE(sv) >= SVt_PVIV); \
                (((XPVUV*) SvANY(sv))->xuv_uv = (val)); } STMT_END
#endif

#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(vnewSVpvf)
#if defined(NEED_vnewSVpvf)
static SV * DPPP_(my_vnewSVpvf)(pTHX_ const char *pat, va_list *args);
static
#else
extern SV * DPPP_(my_vnewSVpvf)(pTHX_ const char *pat, va_list *args);
#endif

#ifdef vnewSVpvf
#  undef vnewSVpvf
#endif
#define vnewSVpvf(a,b) DPPP_(my_vnewSVpvf)(aTHX_ a,b)
#define Perl_vnewSVpvf DPPP_(my_vnewSVpvf)

#if defined(NEED_vnewSVpvf) || defined(NEED_vnewSVpvf_GLOBAL)

SV *
DPPP_(my_vnewSVpvf)(pTHX_ const char *pat, va_list *args)
{
  register SV *sv = newSV(0);
  sv_vsetpvfn(sv, pat, strlen(pat), args, Null(SV**), 0, Null(bool*));
  return sv;
}

#endif
#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_vcatpvf)
#  define sv_vcatpvf(sv, pat, args)  sv_vcatpvfn(sv, pat, strlen(pat), args, Null(SV**), 0, Null(bool*))
#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_vsetpvf)
#  define sv_vsetpvf(sv, pat, args)  sv_vsetpvfn(sv, pat, strlen(pat), args, Null(SV**), 0, Null(bool*))
#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_catpvf_mg)
#if defined(NEED_sv_catpvf_mg)
static void DPPP_(my_sv_catpvf_mg)(pTHX_ SV *sv, const char *pat, ...);
static
#else
extern void DPPP_(my_sv_catpvf_mg)(pTHX_ SV *sv, const char *pat, ...);
#endif

#define Perl_sv_catpvf_mg DPPP_(my_sv_catpvf_mg)

#if defined(NEED_sv_catpvf_mg) || defined(NEED_sv_catpvf_mg_GLOBAL)

void
DPPP_(my_sv_catpvf_mg)(pTHX_ SV *sv, const char *pat, ...)
{
  va_list args;
  va_start(args, pat);
  sv_vcatpvfn(sv, pat, strlen(pat), &args, Null(SV**), 0, Null(bool*));
  SvSETMAGIC(sv);
  va_end(args);
}

#endif
#endif

#ifdef PERL_IMPLICIT_CONTEXT
#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_catpvf_mg_nocontext)
#if defined(NEED_sv_catpvf_mg_nocontext)
static void DPPP_(my_sv_catpvf_mg_nocontext)(SV *sv, const char *pat, ...);
static
#else
extern void DPPP_(my_sv_catpvf_mg_nocontext)(SV *sv, const char *pat, ...);
#endif

#define sv_catpvf_mg_nocontext DPPP_(my_sv_catpvf_mg_nocontext)
#define Perl_sv_catpvf_mg_nocontext DPPP_(my_sv_catpvf_mg_nocontext)

#if defined(NEED_sv_catpvf_mg_nocontext) || defined(NEED_sv_catpvf_mg_nocontext_GLOBAL)

void
DPPP_(my_sv_catpvf_mg_nocontext)(SV *sv, const char *pat, ...)
{
  dTHX;
  va_list args;
  va_start(args, pat);
  sv_vcatpvfn(sv, pat, strlen(pat), &args, Null(SV**), 0, Null(bool*));
  SvSETMAGIC(sv);
  va_end(args);
}

#endif
#endif
#endif

/* sv_catpvf_mg depends on sv_catpvf_mg_nocontext */
#ifndef sv_catpvf_mg
#  ifdef PERL_IMPLICIT_CONTEXT
#    define sv_catpvf_mg   Perl_sv_catpvf_mg_nocontext
#  else
#    define sv_catpvf_mg   Perl_sv_catpvf_mg
#  endif
#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_vcatpvf_mg)
#  define sv_vcatpvf_mg(sv, pat, args)                                     \
   STMT_START {                                                            \
     sv_vcatpvfn(sv, pat, strlen(pat), args, Null(SV**), 0, Null(bool*));  \
     SvSETMAGIC(sv);                                                       \
   } STMT_END
#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_setpvf_mg)
#if defined(NEED_sv_setpvf_mg)
static void DPPP_(my_sv_setpvf_mg)(pTHX_ SV *sv, const char *pat, ...);
static
#else
extern void DPPP_(my_sv_setpvf_mg)(pTHX_ SV *sv, const char *pat, ...);
#endif

#define Perl_sv_setpvf_mg DPPP_(my_sv_setpvf_mg)

#if defined(NEED_sv_setpvf_mg) || defined(NEED_sv_setpvf_mg_GLOBAL)

void
DPPP_(my_sv_setpvf_mg)(pTHX_ SV *sv, const char *pat, ...)
{
  va_list args;
  va_start(args, pat);
  sv_vsetpvfn(sv, pat, strlen(pat), &args, Null(SV**), 0, Null(bool*));
  SvSETMAGIC(sv);
  va_end(args);
}

#endif
#endif

#ifdef PERL_IMPLICIT_CONTEXT
#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_setpvf_mg_nocontext)
#if defined(NEED_sv_setpvf_mg_nocontext)
static void DPPP_(my_sv_setpvf_mg_nocontext)(SV *sv, const char *pat, ...);
static
#else
extern void DPPP_(my_sv_setpvf_mg_nocontext)(SV *sv, const char *pat, ...);
#endif

#define sv_setpvf_mg_nocontext DPPP_(my_sv_setpvf_mg_nocontext)
#define Perl_sv_setpvf_mg_nocontext DPPP_(my_sv_setpvf_mg_nocontext)

#if defined(NEED_sv_setpvf_mg_nocontext) || defined(NEED_sv_setpvf_mg_nocontext_GLOBAL)

void
DPPP_(my_sv_setpvf_mg_nocontext)(SV *sv, const char *pat, ...)
{
  dTHX;
  va_list args;
  va_start(args, pat);
  sv_vsetpvfn(sv, pat, strlen(pat), &args, Null(SV**), 0, Null(bool*));
  SvSETMAGIC(sv);
  va_end(args);
}

#endif
#endif
#endif

/* sv_setpvf_mg depends on sv_setpvf_mg_nocontext */
#ifndef sv_setpvf_mg
#  ifdef PERL_IMPLICIT_CONTEXT
#    define sv_setpvf_mg   Perl_sv_setpvf_mg_nocontext
#  else
#    define sv_setpvf_mg   Perl_sv_setpvf_mg
#  endif
#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(sv_vsetpvf_mg)
#  define sv_vsetpvf_mg(sv, pat, args)                                     \
   STMT_START {                                                            \
     sv_vsetpvfn(sv, pat, strlen(pat), args, Null(SV**), 0, Null(bool*));  \
     SvSETMAGIC(sv);                                                       \
   } STMT_END
#endif

#ifndef newSVpvn_share

#if defined(NEED_newSVpvn_share)
static SV * DPPP_(my_newSVpvn_share)(pTHX_ const char *src, I32 len, U32 hash);
static
#else
extern SV * DPPP_(my_newSVpvn_share)(pTHX_ const char *src, I32 len, U32 hash);
#endif

#ifdef newSVpvn_share
#  undef newSVpvn_share
#endif
#define newSVpvn_share(a,b,c) DPPP_(my_newSVpvn_share)(aTHX_ a,b,c)
#define Perl_newSVpvn_share DPPP_(my_newSVpvn_share)

#if defined(NEED_newSVpvn_share) || defined(NEED_newSVpvn_share_GLOBAL)

SV *
DPPP_(my_newSVpvn_share)(pTHX_ const char *src, I32 len, U32 hash)
{
  SV *sv;
  if (len < 0)
    len = -len;
  if (!hash)
    PERL_HASH(hash, (char*) src, len);
  sv = newSVpvn((char *) src, len);
  sv_upgrade(sv, SVt_PVIV);
  SvIVX(sv) = hash;
  SvREADONLY_on(sv);
  SvPOK_on(sv);
  return sv;
}

#endif

#endif
#ifndef SvSHARED_HASH
#  define SvSHARED_HASH(sv)              (0 + SvUVX(sv))
#endif
#ifndef HvNAME_get
#  define HvNAME_get(hv)                 HvNAME(hv)
#endif
#ifndef HvNAMELEN_get
#  define HvNAMELEN_get(hv)              (HvNAME_get(hv) ? (I32)strlen(HvNAME_get(hv)) : 0)
#endif
#ifndef GvSVn
#  define GvSVn(gv)                      GvSV(gv)
#endif

#ifndef isGV_with_GP
#  define isGV_with_GP(gv)               isGV(gv)
#endif
#ifndef WARN_ALL
#  define WARN_ALL                       0
#endif

#ifndef WARN_CLOSURE
#  define WARN_CLOSURE                   1
#endif

#ifndef WARN_DEPRECATED
#  define WARN_DEPRECATED                2
#endif

#ifndef WARN_EXITING
#  define WARN_EXITING                   3
#endif

#ifndef WARN_GLOB
#  define WARN_GLOB                      4
#endif

#ifndef WARN_IO
#  define WARN_IO                        5
#endif

#ifndef WARN_CLOSED
#  define WARN_CLOSED                    6
#endif

#ifndef WARN_EXEC
#  define WARN_EXEC                      7
#endif

#ifndef WARN_LAYER
#  define WARN_LAYER                     8
#endif

#ifndef WARN_NEWLINE
#  define WARN_NEWLINE                   9
#endif

#ifndef WARN_PIPE
#  define WARN_PIPE                      10
#endif

#ifndef WARN_UNOPENED
#  define WARN_UNOPENED                  11
#endif

#ifndef WARN_MISC
#  define WARN_MISC                      12
#endif

#ifndef WARN_NUMERIC
#  define WARN_NUMERIC                   13
#endif

#ifndef WARN_ONCE
#  define WARN_ONCE                      14
#endif

#ifndef WARN_OVERFLOW
#  define WARN_OVERFLOW                  15
#endif

#ifndef WARN_PACK
#  define WARN_PACK                      16
#endif

#ifndef WARN_PORTABLE
#  define WARN_PORTABLE                  17
#endif

#ifndef WARN_RECURSION
#  define WARN_RECURSION                 18
#endif

#ifndef WARN_REDEFINE
#  define WARN_REDEFINE                  19
#endif

#ifndef WARN_REGEXP
#  define WARN_REGEXP                    20
#endif

#ifndef WARN_SEVERE
#  define WARN_SEVERE                    21
#endif

#ifndef WARN_DEBUGGING
#  define WARN_DEBUGGING                 22
#endif

#ifndef WARN_INPLACE
#  define WARN_INPLACE                   23
#endif

#ifndef WARN_INTERNAL
#  define WARN_INTERNAL                  24
#endif

#ifndef WARN_MALLOC
#  define WARN_MALLOC                    25
#endif

#ifndef WARN_SIGNAL
#  define WARN_SIGNAL                    26
#endif

#ifndef WARN_SUBSTR
#  define WARN_SUBSTR                    27
#endif

#ifndef WARN_SYNTAX
#  define WARN_SYNTAX                    28
#endif

#ifndef WARN_AMBIGUOUS
#  define WARN_AMBIGUOUS                 29
#endif

#ifndef WARN_BAREWORD
#  define WARN_BAREWORD                  30
#endif

#ifndef WARN_DIGIT
#  define WARN_DIGIT                     31
#endif

#ifndef WARN_PARENTHESIS
#  define WARN_PARENTHESIS               32
#endif

#ifndef WARN_PRECEDENCE
#  define WARN_PRECEDENCE                33
#endif

#ifndef WARN_PRINTF
#  define WARN_PRINTF                    34
#endif

#ifndef WARN_PROTOTYPE
#  define WARN_PROTOTYPE                 35
#endif

#ifndef WARN_QW
#  define WARN_QW                        36
#endif

#ifndef WARN_RESERVED
#  define WARN_RESERVED                  37
#endif

#ifndef WARN_SEMICOLON
#  define WARN_SEMICOLON                 38
#endif

#ifndef WARN_TAINT
#  define WARN_TAINT                     39
#endif

#ifndef WARN_THREADS
#  define WARN_THREADS                   40
#endif

#ifndef WARN_UNINITIALIZED
#  define WARN_UNINITIALIZED             41
#endif

#ifndef WARN_UNPACK
#  define WARN_UNPACK                    42
#endif

#ifndef WARN_UNTIE
#  define WARN_UNTIE                     43
#endif

#ifndef WARN_UTF8
#  define WARN_UTF8                      44
#endif

#ifndef WARN_VOID
#  define WARN_VOID                      45
#endif

#ifndef WARN_ASSERTIONS
#  define WARN_ASSERTIONS                46
#endif
#ifndef packWARN
#  define packWARN(a)                    (a)
#endif

#ifndef ckWARN
#  ifdef G_WARN_ON
#    define  ckWARN(a)                  (PL_dowarn & G_WARN_ON)
#  else
#    define  ckWARN(a)                  PL_dowarn
#  endif
#endif

#if (PERL_BCDVERSION >= 0x5004000) && !defined(warner)
#if defined(NEED_warner)
static void DPPP_(my_warner)(U32 err, const char *pat, ...);
static
#else
extern void DPPP_(my_warner)(U32 err, const char *pat, ...);
#endif

#define Perl_warner DPPP_(my_warner)

#if defined(NEED_warner) || defined(NEED_warner_GLOBAL)

void
DPPP_(my_warner)(U32 err, const char *pat, ...)
{
  SV *sv;
  va_list args;

  PERL_UNUSED_ARG(err);

  va_start(args, pat);
  sv = vnewSVpvf(pat, &args);
  va_end(args);
  sv_2mortal(sv);
  warn("%s", SvPV_nolen(sv));
}

#define warner  Perl_warner

#define Perl_warner_nocontext  Perl_warner

#endif
#endif

/* concatenating with "" ensures that only literal strings are accepted as argument
 * note that STR_WITH_LEN() can't be used as argument to macros or functions that
 * under some configurations might be macros
 */
#ifndef STR_WITH_LEN
#  define STR_WITH_LEN(s)                (s ""), (sizeof(s)-1)
#endif
#ifndef newSVpvs
#  define newSVpvs(str)                  newSVpvn(str "", sizeof(str) - 1)
#endif

#ifndef newSVpvs_flags
#  define newSVpvs_flags(str, flags)     newSVpvn_flags(str "", sizeof(str) - 1, flags)
#endif

#ifndef sv_catpvs
#  define sv_catpvs(sv, str)             sv_catpvn(sv, str "", sizeof(str) - 1)
#endif

#ifndef sv_setpvs
#  define sv_setpvs(sv, str)             sv_setpvn(sv, str "", sizeof(str) - 1)
#endif

#ifndef hv_fetchs
#  define hv_fetchs(hv, key, lval)       hv_fetch(hv, key "", sizeof(key) - 1, lval)
#endif

#ifndef hv_stores
#  define hv_stores(hv, key, val)        hv_store(hv, key "", sizeof(key) - 1, val, 0)
#endif
#ifndef gv_fetchpvn_flags
#  define gv_fetchpvn_flags(name, len, flags, svt) gv_fetchpv(name, flags, svt)
#endif

#ifndef gv_fetchpvs
#  define gv_fetchpvs(name, flags, svt)  gv_fetchpvn_flags(name "", sizeof(name) - 1, flags, svt)
#endif

#ifndef gv_stashpvs
#  define gv_stashpvs(name, flags)       gv_stashpvn(name "", sizeof(name) - 1, flags)
#endif
#ifndef SvGETMAGIC
#  define SvGETMAGIC(x)                  STMT_START { if (SvGMAGICAL(x)) mg_get(x); } STMT_END
#endif
#ifndef PERL_MAGIC_sv
#  define PERL_MAGIC_sv                  '\0'
#endif

#ifndef PERL_MAGIC_overload
#  define PERL_MAGIC_overload            'A'
#endif

#ifndef PERL_MAGIC_overload_elem
#  define PERL_MAGIC_overload_elem       'a'
#endif

#ifndef PERL_MAGIC_overload_table
#  define PERL_MAGIC_overload_table      'c'
#endif

#ifndef PERL_MAGIC_bm
#  define PERL_MAGIC_bm                  'B'
#endif

#ifndef PERL_MAGIC_regdata
#  define PERL_MAGIC_regdata             'D'
#endif

#ifndef PERL_MAGIC_regdatum
#  define PERL_MAGIC_regdatum            'd'
#endif

#ifndef PERL_MAGIC_env
#  define PERL_MAGIC_env                 'E'
#endif

#ifndef PERL_MAGIC_envelem
#  define PERL_MAGIC_envelem             'e'
#endif

#ifndef PERL_MAGIC_fm
#  define PERL_MAGIC_fm                  'f'
#endif

#ifndef PERL_MAGIC_regex_global
#  define PERL_MAGIC_regex_global        'g'
#endif

#ifndef PERL_MAGIC_isa
#  define PERL_MAGIC_isa                 'I'
#endif

#ifndef PERL_MAGIC_isaelem
#  define PERL_MAGIC_isaelem             'i'
#endif

#ifndef PERL_MAGIC_nkeys
#  define PERL_MAGIC_nkeys               'k'
#endif

#ifndef PERL_MAGIC_dbfile
#  define PERL_MAGIC_dbfile              'L'
#endif

#ifndef PERL_MAGIC_dbline
#  define PERL_MAGIC_dbline              'l'
#endif

#ifndef PERL_MAGIC_mutex
#  define PERL_MAGIC_mutex               'm'
#endif

#ifndef PERL_MAGIC_shared
#  define PERL_MAGIC_shared              'N'
#endif

#ifndef PERL_MAGIC_shared_scalar
#  define PERL_MAGIC_shared_scalar       'n'
#endif

#ifndef PERL_MAGIC_collxfrm
#  define PERL_MAGIC_collxfrm            'o'
#endif

#ifndef PERL_MAGIC_tied
#  define PERL_MAGIC_tied                'P'
#endif

#ifndef PERL_MAGIC_tiedelem
#  define PERL_MAGIC_tiedelem            'p'
#endif

#ifndef PERL_MAGIC_tiedscalar
#  define PERL_MAGIC_tiedscalar          'q'
#endif

#ifndef PERL_MAGIC_qr
#  define PERL_MAGIC_qr                  'r'
#endif

#ifndef PERL_MAGIC_sig
#  define PERL_MAGIC_sig                 'S'
#endif

#ifndef PERL_MAGIC_sigelem
#  define PERL_MAGIC_sigelem             's'
#endif

#ifndef PERL_MAGIC_taint
#  define PERL_MAGIC_taint               't'
#endif

#ifndef PERL_MAGIC_uvar
#  define PERL_MAGIC_uvar                'U'
#endif

#ifndef PERL_MAGIC_uvar_elem
#  define PERL_MAGIC_uvar_elem           'u'
#endif

#ifndef PERL_MAGIC_vstring
#  define PERL_MAGIC_vstring             'V'
#endif

#ifndef PERL_MAGIC_vec
#  define PERL_MAGIC_vec                 'v'
#endif

#ifndef PERL_MAGIC_utf8
#  define PERL_MAGIC_utf8                'w'
#endif

#ifndef PERL_MAGIC_substr
#  define PERL_MAGIC_substr              'x'
#endif

#ifndef PERL_MAGIC_defelem
#  define PERL_MAGIC_defelem             'y'
#endif

#ifndef PERL_MAGIC_glob
#  define PERL_MAGIC_glob                '*'
#endif

#ifndef PERL_MAGIC_arylen
#  define PERL_MAGIC_arylen              '#'
#endif

#ifndef PERL_MAGIC_pos
#  define PERL_MAGIC_pos                 '.'
#endif

#ifndef PERL_MAGIC_backref
#  define PERL_MAGIC_backref             '<'
#endif

#ifndef PERL_MAGIC_ext
#  define PERL_MAGIC_ext                 '~'
#endif

/* That's the best we can do... */
#ifndef sv_catpvn_nomg
#  define sv_catpvn_nomg                 sv_catpvn
#endif

#ifndef sv_catsv_nomg
#  define sv_catsv_nomg                  sv_catsv
#endif

#ifndef sv_setsv_nomg
#  define sv_setsv_nomg                  sv_setsv
#endif

#ifndef sv_pvn_nomg
#  define sv_pvn_nomg                    sv_pvn
#endif

#ifndef SvIV_nomg
#  define SvIV_nomg                      SvIV
#endif

#ifndef SvUV_nomg
#  define SvUV_nomg                      SvUV
#endif

#ifndef sv_catpv_mg
#  define sv_catpv_mg(sv, ptr)          \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_catpv(TeMpSv,ptr);              \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_catpvn_mg
#  define sv_catpvn_mg(sv, ptr, len)    \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_catpvn(TeMpSv,ptr,len);         \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_catsv_mg
#  define sv_catsv_mg(dsv, ssv)         \
   STMT_START {                         \
     SV *TeMpSv = dsv;                  \
     sv_catsv(TeMpSv,ssv);              \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_setiv_mg
#  define sv_setiv_mg(sv, i)            \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_setiv(TeMpSv,i);                \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_setnv_mg
#  define sv_setnv_mg(sv, num)          \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_setnv(TeMpSv,num);              \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_setpv_mg
#  define sv_setpv_mg(sv, ptr)          \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_setpv(TeMpSv,ptr);              \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_setpvn_mg
#  define sv_setpvn_mg(sv, ptr, len)    \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_setpvn(TeMpSv,ptr,len);         \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_setsv_mg
#  define sv_setsv_mg(dsv, ssv)         \
   STMT_START {                         \
     SV *TeMpSv = dsv;                  \
     sv_setsv(TeMpSv,ssv);              \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_setuv_mg
#  define sv_setuv_mg(sv, i)            \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_setuv(TeMpSv,i);                \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif

#ifndef sv_usepvn_mg
#  define sv_usepvn_mg(sv, ptr, len)    \
   STMT_START {                         \
     SV *TeMpSv = sv;                   \
     sv_usepvn(TeMpSv,ptr,len);         \
     SvSETMAGIC(TeMpSv);                \
   } STMT_END
#endif
#ifndef SvVSTRING_mg
#  define SvVSTRING_mg(sv)               (SvMAGICAL(sv) ? mg_find(sv, PERL_MAGIC_vstring) : NULL)
#endif

/* Hint: sv_magic_portable
 * This is a compatibility function that is only available with
 * Devel::PPPort. It is NOT in the perl core.
 * Its purpose is to mimic the 5.8.0 behaviour of sv_magic() when
 * it is being passed a name pointer with namlen == 0. In that
 * case, perl 5.8.0 and later store the pointer, not a copy of it.
 * The compatibility can be provided back to perl 5.004. With
 * earlier versions, the code will not compile.
 */

#if (PERL_BCDVERSION < 0x5004000)

  /* code that uses sv_magic_portable will not compile */

#elif (PERL_BCDVERSION < 0x5008000)

#  define sv_magic_portable(sv, obj, how, name, namlen)     \
   STMT_START {                                             \
     SV *SvMp_sv = (sv);                                    \
     char *SvMp_name = (char *) (name);                     \
     I32 SvMp_namlen = (namlen);                            \
     if (SvMp_name && SvMp_namlen == 0)                     \
     {                                                      \
       MAGIC *mg;                                           \
       sv_magic(SvMp_sv, obj, how, 0, 0);                   \
       mg = SvMAGIC(SvMp_sv);                               \
       mg->mg_len = -42; /* XXX: this__ is the tricky part */ \
       mg->mg_ptr = SvMp_name;                              \
     }                                                      \
     else                                                   \
     {                                                      \
       sv_magic(SvMp_sv, obj, how, SvMp_name, SvMp_namlen); \
     }                                                      \
   } STMT_END

#else

#  define sv_magic_portable(a, b, c, d, e)  sv_magic(a, b, c, d, e)

#endif

#ifdef USE_ITHREADS
#ifndef CopFILE
#  define CopFILE(c)                     ((c)->cop_file)
#endif

#ifndef CopFILEGV
#  define CopFILEGV(c)                   (CopFILE(c) ? gv_fetchfile(CopFILE(c)) : Nullgv)
#endif

#ifndef CopFILE_set
#  define CopFILE_set(c,pv)              ((c)->cop_file = savepv(pv))
#endif

#ifndef CopFILESV
#  define CopFILESV(c)                   (CopFILE(c) ? GvSV(gv_fetchfile(CopFILE(c))) : Nullsv)
#endif

#ifndef CopFILEAV
#  define CopFILEAV(c)                   (CopFILE(c) ? GvAV(gv_fetchfile(CopFILE(c))) : Nullav)
#endif

#ifndef CopSTASHPV
#  define CopSTASHPV(c)                  ((c)->cop_stashpv)
#endif

#ifndef CopSTASHPV_set
#  define CopSTASHPV_set(c,pv)           ((c)->cop_stashpv = ((pv) ? savepv(pv) : Nullch))
#endif

#ifndef CopSTASH
#  define CopSTASH(c)                    (CopSTASHPV(c) ? gv_stashpv(CopSTASHPV(c),GV_ADD) : Nullhv)
#endif

#ifndef CopSTASH_set
#  define CopSTASH_set(c,hv)             CopSTASHPV_set(c, (hv) ? HvNAME(hv) : Nullch)
#endif

#ifndef CopSTASH_eq
#  define CopSTASH_eq(c,hv)              ((hv) && (CopSTASHPV(c) == HvNAME(hv) \
					|| (CopSTASHPV(c) && HvNAME(hv) \
					&& strEQ(CopSTASHPV(c), HvNAME(hv)))))
#endif

#else
#ifndef CopFILEGV
#  define CopFILEGV(c)                   ((c)->cop_filegv)
#endif

#ifndef CopFILEGV_set
#  define CopFILEGV_set(c,gv)            ((c)->cop_filegv = (GV*)SvREFCNT_inc(gv))
#endif

#ifndef CopFILE_set
#  define CopFILE_set(c,pv)              CopFILEGV_set((c), gv_fetchfile(pv))
#endif

#ifndef CopFILESV
#  define CopFILESV(c)                   (CopFILEGV(c) ? GvSV(CopFILEGV(c)) : Nullsv)
#endif

#ifndef CopFILEAV
#  define CopFILEAV(c)                   (CopFILEGV(c) ? GvAV(CopFILEGV(c)) : Nullav)
#endif

#ifndef CopFILE
#  define CopFILE(c)                     (CopFILESV(c) ? SvPVX(CopFILESV(c)) : Nullch)
#endif

#ifndef CopSTASH
#  define CopSTASH(c)                    ((c)->cop_stash)
#endif

#ifndef CopSTASH_set
#  define CopSTASH_set(c,hv)             ((c)->cop_stash = (hv))
#endif

#ifndef CopSTASHPV
#  define CopSTASHPV(c)                  (CopSTASH(c) ? HvNAME(CopSTASH(c)) : Nullch)
#endif

#ifndef CopSTASHPV_set
#  define CopSTASHPV_set(c,pv)           CopSTASH_set((c), gv_stashpv(pv,GV_ADD))
#endif

#ifndef CopSTASH_eq
#  define CopSTASH_eq(c,hv)              (CopSTASH(c) == (hv))
#endif

#endif /* USE_ITHREADS */
#ifndef IN_PERL_COMPILETIME
#  define IN_PERL_COMPILETIME            (PL_curcop == &PL_compiling)
#endif

#ifndef IN_LOCALE_RUNTIME
#  define IN_LOCALE_RUNTIME              (PL_curcop->op_private & HINT_LOCALE)
#endif

#ifndef IN_LOCALE_COMPILETIME
#  define IN_LOCALE_COMPILETIME          (PL_hints & HINT_LOCALE)
#endif

#ifndef IN_LOCALE
#  define IN_LOCALE                      (IN_PERL_COMPILETIME ? IN_LOCALE_COMPILETIME : IN_LOCALE_RUNTIME)
#endif
#ifndef IS_NUMBER_IN_UV
#  define IS_NUMBER_IN_UV                0x01
#endif

#ifndef IS_NUMBER_GREATER_THAN_UV_MAX
#  define IS_NUMBER_GREATER_THAN_UV_MAX  0x02
#endif

#ifndef IS_NUMBER_NOT_INT
#  define IS_NUMBER_NOT_INT              0x04
#endif

#ifndef IS_NUMBER_NEG
#  define IS_NUMBER_NEG                  0x08
#endif

#ifndef IS_NUMBER_INFINITY
#  define IS_NUMBER_INFINITY             0x10
#endif

#ifndef IS_NUMBER_NAN
#  define IS_NUMBER_NAN                  0x20
#endif
#ifndef GROK_NUMERIC_RADIX
#  define GROK_NUMERIC_RADIX(sp, send)   grok_numeric_radix(sp, send)
#endif
#ifndef PERL_SCAN_GREATER_THAN_UV_MAX
#  define PERL_SCAN_GREATER_THAN_UV_MAX  0x02
#endif

#ifndef PERL_SCAN_SILENT_ILLDIGIT
#  define PERL_SCAN_SILENT_ILLDIGIT      0x04
#endif

#ifndef PERL_SCAN_ALLOW_UNDERSCORES
#  define PERL_SCAN_ALLOW_UNDERSCORES    0x01
#endif

#ifndef PERL_SCAN_DISALLOW_PREFIX
#  define PERL_SCAN_DISALLOW_PREFIX      0x02
#endif

#ifndef grok_numeric_radix
#if defined(NEED_grok_numeric_radix)
static bool DPPP_(my_grok_numeric_radix)(pTHX_ const char ** sp, const char * send);
static
#else
extern bool DPPP_(my_grok_numeric_radix)(pTHX_ const char ** sp, const char * send);
#endif

#ifdef grok_numeric_radix
#  undef grok_numeric_radix
#endif
#define grok_numeric_radix(a,b) DPPP_(my_grok_numeric_radix)(aTHX_ a,b)
#define Perl_grok_numeric_radix DPPP_(my_grok_numeric_radix)

#if defined(NEED_grok_numeric_radix) || defined(NEED_grok_numeric_radix_GLOBAL)
bool
DPPP_(my_grok_numeric_radix)(pTHX_ const char **sp, const char *send)
{
#ifdef USE_LOCALE_NUMERIC
#ifdef PL_numeric_radix_sv
    if (PL_numeric_radix_sv && IN_LOCALE) {
        STRLEN len;
        char* radix = SvPV(PL_numeric_radix_sv, len);
        if (*sp + len <= send && memEQ(*sp, radix, len)) {
            *sp += len;
            return TRUE;
        }
    }
#else
    /* older perls don't have PL_numeric_radix_sv so the radix
     * must manually be requested from locale.h
     */
#include <locale.h>
    dTHR;  /* needed for older threaded perls */
    struct lconv *lc = localeconv();
    char *radix = lc->decimal_point;
    if (radix && IN_LOCALE) {
        STRLEN len = strlen(radix);
        if (*sp + len <= send && memEQ(*sp, radix, len)) {
            *sp += len;
            return TRUE;
        }
    }
#endif
#endif /* USE_LOCALE_NUMERIC */
    /* always try "." if numeric radix didn't match because
     * we may have data from different locales mixed */
    if (*sp < send && **sp == '.') {
        ++*sp;
        return TRUE;
    }
    return FALSE;
}
#endif
#endif

#ifndef grok_number
#if defined(NEED_grok_number)
static int DPPP_(my_grok_number)(pTHX_ const char * pv, STRLEN len, UV * valuep);
static
#else
extern int DPPP_(my_grok_number)(pTHX_ const char * pv, STRLEN len, UV * valuep);
#endif

#ifdef grok_number
#  undef grok_number
#endif
#define grok_number(a,b,c) DPPP_(my_grok_number)(aTHX_ a,b,c)
#define Perl_grok_number DPPP_(my_grok_number)

#if defined(NEED_grok_number) || defined(NEED_grok_number_GLOBAL)
int
DPPP_(my_grok_number)(pTHX_ const char *pv, STRLEN len, UV *valuep)
{
  const char *s = pv;
  const char *send = pv + len;
  const UV max_div_10 = UV_MAX / 10;
  const char max_mod_10 = UV_MAX % 10;
  int numtype = 0;
  int sawinf = 0;
  int sawnan = 0;

  while (s < send && isSPACE(*s))
    s++;
  if (s == send) {
    return 0;
  } else if (*s == '-') {
    s++;
    numtype = IS_NUMBER_NEG;
  }
  else if (*s == '+')
  s++;

  if (s == send)
    return 0;

  /* next must be digit or the radix separator or beginning of infinity */
  if (isDIGIT(*s)) {
    /* UVs are at least 32 bits, so the first 9 decimal digits cannot
       overflow.  */
    UV value = *s - '0';
    /* This construction seems to be more optimiser friendly.
       (without it gcc does the isDIGIT test and the *s - '0' separately)
       With it gcc on arm is managing 6 instructions (6 cycles) per digit.
       In theory the optimiser could deduce how far to unroll the loop
       before checking for overflow.  */
    if (++s < send) {
      int digit = *s - '0';
      if (digit >= 0 && digit <= 9) {
        value = value * 10 + digit;
        if (++s < send) {
          digit = *s - '0';
          if (digit >= 0 && digit <= 9) {
            value = value * 10 + digit;
            if (++s < send) {
              digit = *s - '0';
              if (digit >= 0 && digit <= 9) {
                value = value * 10 + digit;
		if (++s < send) {
                  digit = *s - '0';
                  if (digit >= 0 && digit <= 9) {
                    value = value * 10 + digit;
                    if (++s < send) {
                      digit = *s - '0';
                      if (digit >= 0 && digit <= 9) {
                        value = value * 10 + digit;
                        if (++s < send) {
                          digit = *s - '0';
                          if (digit >= 0 && digit <= 9) {
                            value = value * 10 + digit;
                            if (++s < send) {
                              digit = *s - '0';
                              if (digit >= 0 && digit <= 9) {
                                value = value * 10 + digit;
                                if (++s < send) {
                                  digit = *s - '0';
                                  if (digit >= 0 && digit <= 9) {
                                    value = value * 10 + digit;
                                    if (++s < send) {
                                      /* Now got 9 digits, so need to check
                                         each time for overflow.  */
                                      digit = *s - '0';
                                      while (digit >= 0 && digit <= 9
                                             && (value < max_div_10
                                                 || (value == max_div_10
                                                     && digit <= max_mod_10))) {
                                        value = value * 10 + digit;
                                        if (++s < send)
                                          digit = *s - '0';
                                        else
                                          break;
                                      }
                                      if (digit >= 0 && digit <= 9
                                          && (s < send)) {
                                        /* value overflowed.
                                           skip the remaining digits, don't
                                           worry about setting *valuep.  */
                                        do {
                                          s++;
                                        } while (s < send && isDIGIT(*s));
                                        numtype |=
                                          IS_NUMBER_GREATER_THAN_UV_MAX;
                                        goto skip_value;
                                      }
                                    }
                                  }
				}
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
	}
      }
    }
    numtype |= IS_NUMBER_IN_UV;
    if (valuep)
      *valuep = value;

  skip_value:
    if (GROK_NUMERIC_RADIX(&s, send)) {
      numtype |= IS_NUMBER_NOT_INT;
      while (s < send && isDIGIT(*s))  /* optional digits after the radix */
        s++;
    }
  }
  else if (GROK_NUMERIC_RADIX(&s, send)) {
    numtype |= IS_NUMBER_NOT_INT | IS_NUMBER_IN_UV; /* valuep assigned below */
    /* no digits before the radix means we need digits after it */
    if (s < send && isDIGIT(*s)) {
      do {
        s++;
      } while (s < send && isDIGIT(*s));
      if (valuep) {
        /* integer approximation is valid - it's 0.  */
        *valuep = 0;
      }
    }
    else
      return 0;
  } else if (*s == 'I' || *s == 'i') {
    s++; if (s == send || (*s != 'N' && *s != 'n')) return 0;
    s++; if (s == send || (*s != 'F' && *s != 'f')) return 0;
    s++; if (s < send && (*s == 'I' || *s == 'i')) {
      s++; if (s == send || (*s != 'N' && *s != 'n')) return 0;
      s++; if (s == send || (*s != 'I' && *s != 'i')) return 0;
      s++; if (s == send || (*s != 'T' && *s != 't')) return 0;
      s++; if (s == send || (*s != 'Y' && *s != 'y')) return 0;
      s++;
    }
    sawinf = 1;
  } else if (*s == 'N' || *s == 'n') {
    /* XXX TODO: There are signaling NaNs and quiet NaNs. */
    s++; if (s == send || (*s != 'A' && *s != 'a')) return 0;
    s++; if (s == send || (*s != 'N' && *s != 'n')) return 0;
    s++;
    sawnan = 1;
  } else
    return 0;

  if (sawinf) {
    numtype &= IS_NUMBER_NEG; /* Keep track of sign  */
    numtype |= IS_NUMBER_INFINITY | IS_NUMBER_NOT_INT;
  } else if (sawnan) {
    numtype &= IS_NUMBER_NEG; /* Keep track of sign  */
    numtype |= IS_NUMBER_NAN | IS_NUMBER_NOT_INT;
  } else if (s < send) {
    /* we can have an optional exponent part */
    if (*s == 'e' || *s == 'E') {
      /* The only flag we keep is sign.  Blow away any "it's UV"  */
      numtype &= IS_NUMBER_NEG;
      numtype |= IS_NUMBER_NOT_INT;
      s++;
      if (s < send && (*s == '-' || *s == '+'))
        s++;
      if (s < send && isDIGIT(*s)) {
        do {
          s++;
        } while (s < send && isDIGIT(*s));
      }
      else
      return 0;
    }
  }
  while (s < send && isSPACE(*s))
    s++;
  if (s >= send)
    return numtype;
  if (len == 10 && memEQ(pv, "0 but true", 10)) {
    if (valuep)
      *valuep = 0;
    return IS_NUMBER_IN_UV;
  }
  return 0;
}
#endif
#endif

/*
 * The grok_* routines have been modified to use warn() instead of
 * Perl_warner(). Also, 'hexdigit' was the former name of PL_hexdigit,
 * which is why the stack variable has been renamed to 'xdigit'.
 */

#ifndef grok_bin
#if defined(NEED_grok_bin)
static UV DPPP_(my_grok_bin)(pTHX_ const char * start, STRLEN * len_p, I32 * flags, NV * result);
static
#else
extern UV DPPP_(my_grok_bin)(pTHX_ const char * start, STRLEN * len_p, I32 * flags, NV * result);
#endif

#ifdef grok_bin
#  undef grok_bin
#endif
#define grok_bin(a,b,c,d) DPPP_(my_grok_bin)(aTHX_ a,b,c,d)
#define Perl_grok_bin DPPP_(my_grok_bin)

#if defined(NEED_grok_bin) || defined(NEED_grok_bin_GLOBAL)
UV
DPPP_(my_grok_bin)(pTHX_ const char *start, STRLEN *len_p, I32 *flags, NV *result)
{
    const char *s = start;
    STRLEN len = *len_p;
    UV value = 0;
    NV value_nv = 0;

    const UV max_div_2 = UV_MAX / 2;
    bool allow_underscores = *flags & PERL_SCAN_ALLOW_UNDERSCORES;
    bool overflowed = FALSE;

    if (!(*flags & PERL_SCAN_DISALLOW_PREFIX)) {
        /* strip off leading b or 0b.
           for compatibility silently suffer "b" and "0b" as valid binary
           numbers. */
        if (len >= 1) {
            if (s[0] == 'b') {
                s++;
                len--;
            }
            else if (len >= 2 && s[0] == '0' && s[1] == 'b') {
                s+=2;
                len-=2;
            }
        }
    }

    for (; len-- && *s; s++) {
        char bit = *s;
        if (bit == '0' || bit == '1') {
            /* Write it in this__ wonky order with a goto to attempt to get the
               compiler to make the common case integer-only loop pretty tight.
               With gcc seems to be much straighter code than old scan_bin.  */
          redo:
            if (!overflowed) {
                if (value <= max_div_2) {
                    value = (value << 1) | (bit - '0');
                    continue;
                }
                /* Bah. We're just overflowed.  */
                warn("Integer overflow in binary number");
                overflowed = TRUE;
                value_nv = (NV) value;
            }
            value_nv *= 2.0;
	    /* If an NV has not enough bits in its mantissa to
	     * represent a UV this__ summing of small low-order numbers
	     * is a waste of time (because the NV cannot preserve
	     * the low-order bits anyway): we could just remember when
	     * did we overflow and in the end just multiply value_nv by the
	     * right amount. */
            value_nv += (NV)(bit - '0');
            continue;
        }
        if (bit == '_' && len && allow_underscores && (bit = s[1])
            && (bit == '0' || bit == '1'))
	    {
		--len;
		++s;
                goto redo;
	    }
        if (!(*flags & PERL_SCAN_SILENT_ILLDIGIT))
            warn("Illegal binary digit '%c' ignored", *s);
        break;
    }

    if (   ( overflowed && value_nv > 4294967295.0)
#if UVSIZE > 4
	|| (!overflowed && value > 0xffffffff  )
#endif
	) {
	warn("Binary number > 0b11111111111111111111111111111111 non-portable");
    }
    *len_p = s - start;
    if (!overflowed) {
        *flags = 0;
        return value;
    }
    *flags = PERL_SCAN_GREATER_THAN_UV_MAX;
    if (result)
        *result = value_nv;
    return UV_MAX;
}
#endif
#endif

#ifndef grok_hex
#if defined(NEED_grok_hex)
static UV DPPP_(my_grok_hex)(pTHX_ const char * start, STRLEN * len_p, I32 * flags, NV * result);
static
#else
extern UV DPPP_(my_grok_hex)(pTHX_ const char * start, STRLEN * len_p, I32 * flags, NV * result);
#endif

#ifdef grok_hex
#  undef grok_hex
#endif
#define grok_hex(a,b,c,d) DPPP_(my_grok_hex)(aTHX_ a,b,c,d)
#define Perl_grok_hex DPPP_(my_grok_hex)

#if defined(NEED_grok_hex) || defined(NEED_grok_hex_GLOBAL)
UV
DPPP_(my_grok_hex)(pTHX_ const char *start, STRLEN *len_p, I32 *flags, NV *result)
{
    const char *s = start;
    STRLEN len = *len_p;
    UV value = 0;
    NV value_nv = 0;

    const UV max_div_16 = UV_MAX / 16;
    bool allow_underscores = *flags & PERL_SCAN_ALLOW_UNDERSCORES;
    bool overflowed = FALSE;
    const char *xdigit;

    if (!(*flags & PERL_SCAN_DISALLOW_PREFIX)) {
        /* strip off leading x or 0x.
           for compatibility silently suffer "x" and "0x" as valid hex numbers.
        */
        if (len >= 1) {
            if (s[0] == 'x') {
                s++;
                len--;
            }
            else if (len >= 2 && s[0] == '0' && s[1] == 'x') {
                s+=2;
                len-=2;
            }
        }
    }

    for (; len-- && *s; s++) {
	xdigit = strchr((char *) PL_hexdigit, *s);
        if (xdigit) {
            /* Write it in this__ wonky order with a goto to attempt to get the
               compiler to make the common case integer-only loop pretty tight.
               With gcc seems to be much straighter code than old scan_hex.  */
          redo:
            if (!overflowed) {
                if (value <= max_div_16) {
                    value = (value << 4) | ((xdigit - PL_hexdigit) & 15);
                    continue;
                }
                warn("Integer overflow in hexadecimal number");
                overflowed = TRUE;
                value_nv = (NV) value;
            }
            value_nv *= 16.0;
	    /* If an NV has not enough bits in its mantissa to
	     * represent a UV this__ summing of small low-order numbers
	     * is a waste of time (because the NV cannot preserve
	     * the low-order bits anyway): we could just remember when
	     * did we overflow and in the end just multiply value_nv by the
	     * right amount of 16-tuples. */
            value_nv += (NV)((xdigit - PL_hexdigit) & 15);
            continue;
        }
        if (*s == '_' && len && allow_underscores && s[1]
		&& (xdigit = strchr((char *) PL_hexdigit, s[1])))
	    {
		--len;
		++s;
                goto redo;
	    }
        if (!(*flags & PERL_SCAN_SILENT_ILLDIGIT))
            warn("Illegal hexadecimal digit '%c' ignored", *s);
        break;
    }

    if (   ( overflowed && value_nv > 4294967295.0)
#if UVSIZE > 4
	|| (!overflowed && value > 0xffffffff  )
#endif
	) {
	warn("Hexadecimal number > 0xffffffff non-portable");
    }
    *len_p = s - start;
    if (!overflowed) {
        *flags = 0;
        return value;
    }
    *flags = PERL_SCAN_GREATER_THAN_UV_MAX;
    if (result)
        *result = value_nv;
    return UV_MAX;
}
#endif
#endif

#ifndef grok_oct
#if defined(NEED_grok_oct)
static UV DPPP_(my_grok_oct)(pTHX_ const char * start, STRLEN * len_p, I32 * flags, NV * result);
static
#else
extern UV DPPP_(my_grok_oct)(pTHX_ const char * start, STRLEN * len_p, I32 * flags, NV * result);
#endif

#ifdef grok_oct
#  undef grok_oct
#endif
#define grok_oct(a,b,c,d) DPPP_(my_grok_oct)(aTHX_ a,b,c,d)
#define Perl_grok_oct DPPP_(my_grok_oct)

#if defined(NEED_grok_oct) || defined(NEED_grok_oct_GLOBAL)
UV
DPPP_(my_grok_oct)(pTHX_ const char *start, STRLEN *len_p, I32 *flags, NV *result)
{
    const char *s = start;
    STRLEN len = *len_p;
    UV value = 0;
    NV value_nv = 0;

    const UV max_div_8 = UV_MAX / 8;
    bool allow_underscores = *flags & PERL_SCAN_ALLOW_UNDERSCORES;
    bool overflowed = FALSE;

    for (; len-- && *s; s++) {
         /* gcc 2.95 optimiser not smart enough to figure that this__ subtraction
            out front allows slicker code.  */
        int digit = *s - '0';
        if (digit >= 0 && digit <= 7) {
            /* Write it in this__ wonky order with a goto to attempt to get the
               compiler to make the common case integer-only loop pretty tight.
            */
          redo:
            if (!overflowed) {
                if (value <= max_div_8) {
                    value = (value << 3) | digit;
                    continue;
                }
                /* Bah. We're just overflowed.  */
                warn("Integer overflow in octal number");
                overflowed = TRUE;
                value_nv = (NV) value;
            }
            value_nv *= 8.0;
	    /* If an NV has not enough bits in its mantissa to
	     * represent a UV this__ summing of small low-order numbers
	     * is a waste of time (because the NV cannot preserve
	     * the low-order bits anyway): we could just remember when
	     * did we overflow and in the end just multiply value_nv by the
	     * right amount of 8-tuples. */
            value_nv += (NV)digit;
            continue;
        }
        if (digit == ('_' - '0') && len && allow_underscores
            && (digit = s[1] - '0') && (digit >= 0 && digit <= 7))
	    {
		--len;
		++s;
                goto redo;
	    }
        /* Allow \octal to work the DWIM way (that is, stop scanning
         * as soon as non-octal characters are seen, complain only iff
         * someone seems to want to use the digits eight and nine). */
        if (digit == 8 || digit == 9) {
            if (!(*flags & PERL_SCAN_SILENT_ILLDIGIT))
                warn("Illegal octal digit '%c' ignored", *s);
        }
        break;
    }

    if (   ( overflowed && value_nv > 4294967295.0)
#if UVSIZE > 4
	|| (!overflowed && value > 0xffffffff  )
#endif
	) {
	warn("Octal number > 037777777777 non-portable");
    }
    *len_p = s - start;
    if (!overflowed) {
        *flags = 0;
        return value;
    }
    *flags = PERL_SCAN_GREATER_THAN_UV_MAX;
    if (result)
        *result = value_nv;
    return UV_MAX;
}
#endif
#endif

#if !defined(my_snprintf)
#if defined(NEED_my_snprintf)
static int DPPP_(my_my_snprintf)(char * buffer, const Size_t len, const char * format, ...);
static
#else
extern int DPPP_(my_my_snprintf)(char * buffer, const Size_t len, const char * format, ...);
#endif

#define my_snprintf DPPP_(my_my_snprintf)
#define Perl_my_snprintf DPPP_(my_my_snprintf)

#if defined(NEED_my_snprintf) || defined(NEED_my_snprintf_GLOBAL)

int
DPPP_(my_my_snprintf)(char *buffer, const Size_t len, const char *format, ...)
{
    dTHX;
    int retval;
    va_list ap;
    va_start(ap, format);
#ifdef HAS_VSNPRINTF
    retval = vsnprintf(buffer, len, format, ap);
#else
    retval = vsprintf(buffer, format, ap);
#endif
    va_end(ap);
    if (retval < 0 || (len > 0 && (Size_t)retval >= len))
	Perl_croak(aTHX_ "panic: my_snprintf buffer overflow");
    return retval;
}

#endif
#endif

#if !defined(my_sprintf)
#if defined(NEED_my_sprintf)
static int DPPP_(my_my_sprintf)(char * buffer, const char * pat, ...);
static
#else
extern int DPPP_(my_my_sprintf)(char * buffer, const char * pat, ...);
#endif

#define my_sprintf DPPP_(my_my_sprintf)
#define Perl_my_sprintf DPPP_(my_my_sprintf)

#if defined(NEED_my_sprintf) || defined(NEED_my_sprintf_GLOBAL)

int
DPPP_(my_my_sprintf)(char *buffer, const char* pat, ...)
{
    va_list args;
    va_start(args, pat);
    vsprintf(buffer, pat, args);
    va_end(args);
    return strlen(buffer);
}

#endif
#endif

#ifdef NO_XSLOCKS
#  ifdef dJMPENV
#    define dXCPT             dJMPENV; int rEtV = 0
#    define XCPT_TRY_START    JMPENV_PUSH(rEtV); if (rEtV == 0)
#    define XCPT_TRY_END      JMPENV_POP;
#    define XCPT_CATCH        if (rEtV != 0)
#    define XCPT_RETHROW      JMPENV_JUMP(rEtV)
#  else
#    define dXCPT             Sigjmp_buf oldTOP; int rEtV = 0
#    define XCPT_TRY_START    Copy(top_env, oldTOP, 1, Sigjmp_buf); rEtV = Sigsetjmp(top_env, 1); if (rEtV == 0)
#    define XCPT_TRY_END      Copy(oldTOP, top_env, 1, Sigjmp_buf);
#    define XCPT_CATCH        if (rEtV != 0)
#    define XCPT_RETHROW      Siglongjmp(top_env, rEtV)
#  endif
#endif

#if !defined(my_strlcat)
#if defined(NEED_my_strlcat)
static Size_t DPPP_(my_my_strlcat)(char * dst, const char * src, Size_t size);
static
#else
extern Size_t DPPP_(my_my_strlcat)(char * dst, const char * src, Size_t size);
#endif

#define my_strlcat DPPP_(my_my_strlcat)
#define Perl_my_strlcat DPPP_(my_my_strlcat)

#if defined(NEED_my_strlcat) || defined(NEED_my_strlcat_GLOBAL)

Size_t
DPPP_(my_my_strlcat)(char *dst, const char *src, Size_t size)
{
    Size_t used, length, copy;

    used = strlen(dst);
    length = strlen(src);
    if (size > 0 && used < size - 1) {
        copy = (length >= size - used) ? size - used - 1 : length;
        memcpy(dst + used, src, copy);
        dst[used + copy] = '\0';
    }
    return used + length;
}
#endif
#endif

#if !defined(my_strlcpy)
#if defined(NEED_my_strlcpy)
static Size_t DPPP_(my_my_strlcpy)(char * dst, const char * src, Size_t size);
static
#else
extern Size_t DPPP_(my_my_strlcpy)(char * dst, const char * src, Size_t size);
#endif

#define my_strlcpy DPPP_(my_my_strlcpy)
#define Perl_my_strlcpy DPPP_(my_my_strlcpy)

#if defined(NEED_my_strlcpy) || defined(NEED_my_strlcpy_GLOBAL)

Size_t
DPPP_(my_my_strlcpy)(char *dst, const char *src, Size_t size)
{
    Size_t length, copy;

    length = strlen(src);
    if (size > 0) {
        copy = (length >= size) ? size - 1 : length;
        memcpy(dst, src, copy);
        dst[copy] = '\0';
    }
    return length;
}

#endif
#endif
#ifndef PERL_PV_ESCAPE_QUOTE
#  define PERL_PV_ESCAPE_QUOTE           0x0001
#endif

#ifndef PERL_PV_PRETTY_QUOTE
#  define PERL_PV_PRETTY_QUOTE           PERL_PV_ESCAPE_QUOTE
#endif

#ifndef PERL_PV_PRETTY_ELLIPSES
#  define PERL_PV_PRETTY_ELLIPSES        0x0002
#endif

#ifndef PERL_PV_PRETTY_LTGT
#  define PERL_PV_PRETTY_LTGT            0x0004
#endif

#ifndef PERL_PV_ESCAPE_FIRSTCHAR
#  define PERL_PV_ESCAPE_FIRSTCHAR       0x0008
#endif

#ifndef PERL_PV_ESCAPE_UNI
#  define PERL_PV_ESCAPE_UNI             0x0100
#endif

#ifndef PERL_PV_ESCAPE_UNI_DETECT
#  define PERL_PV_ESCAPE_UNI_DETECT      0x0200
#endif

#ifndef PERL_PV_ESCAPE_ALL
#  define PERL_PV_ESCAPE_ALL             0x1000
#endif

#ifndef PERL_PV_ESCAPE_NOBACKSLASH
#  define PERL_PV_ESCAPE_NOBACKSLASH     0x2000
#endif

#ifndef PERL_PV_ESCAPE_NOCLEAR
#  define PERL_PV_ESCAPE_NOCLEAR         0x4000
#endif

#ifndef PERL_PV_ESCAPE_RE
#  define PERL_PV_ESCAPE_RE              0x8000
#endif

#ifndef PERL_PV_PRETTY_NOCLEAR
#  define PERL_PV_PRETTY_NOCLEAR         PERL_PV_ESCAPE_NOCLEAR
#endif
#ifndef PERL_PV_PRETTY_DUMP
#  define PERL_PV_PRETTY_DUMP            PERL_PV_PRETTY_ELLIPSES|PERL_PV_PRETTY_QUOTE
#endif

#ifndef PERL_PV_PRETTY_REGPROP
#  define PERL_PV_PRETTY_REGPROP         PERL_PV_PRETTY_ELLIPSES|PERL_PV_PRETTY_LTGT|PERL_PV_ESCAPE_RE
#endif

/* Hint: pv_escape
 * Note that unicode functionality is only backported to
 * those perl versions that support it. For older perl
 * versions, the implementation will fall back to bytes.
 */

#ifndef pv_escape
#if defined(NEED_pv_escape)
static char * DPPP_(my_pv_escape)(pTHX_ SV * dsv, char const * const str, const STRLEN count, const STRLEN max, STRLEN * const escaped, const U32 flags);
static
#else
extern char * DPPP_(my_pv_escape)(pTHX_ SV * dsv, char const * const str, const STRLEN count, const STRLEN max, STRLEN * const escaped, const U32 flags);
#endif

#ifdef pv_escape
#  undef pv_escape
#endif
#define pv_escape(a,b,c,d,e,f) DPPP_(my_pv_escape)(aTHX_ a,b,c,d,e,f)
#define Perl_pv_escape DPPP_(my_pv_escape)

#if defined(NEED_pv_escape) || defined(NEED_pv_escape_GLOBAL)

char *
DPPP_(my_pv_escape)(pTHX_ SV *dsv, char const * const str,
  const STRLEN count, const STRLEN max,
  STRLEN * const escaped, const U32 flags)
{
    const char esc = flags & PERL_PV_ESCAPE_RE ? '%' : '\\';
    const char dq = flags & PERL_PV_ESCAPE_QUOTE ? '"' : esc;
    char octbuf[32] = "%123456789ABCDF";
    STRLEN wrote = 0;
    STRLEN chsize = 0;
    STRLEN readsize = 1;
#if defined(is_utf8_string) && defined(utf8_to_uvchr)
    bool isuni = flags & PERL_PV_ESCAPE_UNI ? 1 : 0;
#endif
    const char *pv  = str;
    const char * const end = pv + count;
    octbuf[0] = esc;

    if (!(flags & PERL_PV_ESCAPE_NOCLEAR))
	sv_setpvs(dsv, "");

#if defined(is_utf8_string) && defined(utf8_to_uvchr)
    if ((flags & PERL_PV_ESCAPE_UNI_DETECT) && is_utf8_string((U8*)pv, count))
        isuni = 1;
#endif

    for (; pv < end && (!max || wrote < max) ; pv += readsize) {
        const UV u =
#if defined(is_utf8_string) && defined(utf8_to_uvchr)
		     isuni ? utf8_to_uvchr((U8*)pv, &readsize) :
#endif
			     (U8)*pv;
        const U8 c = (U8)u & 0xFF;

        if (u > 255 || (flags & PERL_PV_ESCAPE_ALL)) {
            if (flags & PERL_PV_ESCAPE_FIRSTCHAR)
                chsize = my_snprintf(octbuf, sizeof octbuf,
                                      "%"UVxf, u);
            else
                chsize = my_snprintf(octbuf, sizeof octbuf,
                                      "%cx{%"UVxf"}", esc, u);
        } else if (flags & PERL_PV_ESCAPE_NOBACKSLASH) {
            chsize = 1;
        } else {
            if (c == dq || c == esc || !isPRINT(c)) {
	        chsize = 2;
                switch (c) {
		case '\\' : /* fallthrough */
		case '%'  : if (c == esc)
		                octbuf[1] = esc;
		            else
		                chsize = 1;
		            break;
		case '\v' : octbuf[1] = 'v'; break;
		case '\t' : octbuf[1] = 't'; break;
		case '\r' : octbuf[1] = 'r'; break;
		case '\n' : octbuf[1] = 'n'; break;
		case '\f' : octbuf[1] = 'f'; break;
                case '"'  : if (dq == '"')
				octbuf[1] = '"';
			    else
				chsize = 1;
			    break;
		default:    chsize = my_snprintf(octbuf, sizeof octbuf,
				pv < end && isDIGIT((U8)*(pv+readsize))
				? "%c%03o" : "%c%o", esc, c);
                }
            } else {
                chsize = 1;
            }
	}
	if (max && wrote + chsize > max) {
	    break;
        } else if (chsize > 1) {
            sv_catpvn(dsv, octbuf, chsize);
            wrote += chsize;
	} else {
	    char tmp[2];
	    my_snprintf(tmp, sizeof tmp, "%c", c);
            sv_catpvn(dsv, tmp, 1);
	    wrote++;
	}
        if (flags & PERL_PV_ESCAPE_FIRSTCHAR)
            break;
    }
    if (escaped != NULL)
        *escaped= pv - str;
    return SvPVX(dsv);
}

#endif
#endif

#ifndef pv_pretty
#if defined(NEED_pv_pretty)
static char * DPPP_(my_pv_pretty)(pTHX_ SV * dsv, char const * const str, const STRLEN count, const STRLEN max, char const * const start_color, char const * const end_color, const U32 flags);
static
#else
extern char * DPPP_(my_pv_pretty)(pTHX_ SV * dsv, char const * const str, const STRLEN count, const STRLEN max, char const * const start_color, char const * const end_color, const U32 flags);
#endif

#ifdef pv_pretty
#  undef pv_pretty
#endif
#define pv_pretty(a,b,c,d,e,f,g) DPPP_(my_pv_pretty)(aTHX_ a,b,c,d,e,f,g)
#define Perl_pv_pretty DPPP_(my_pv_pretty)

#if defined(NEED_pv_pretty) || defined(NEED_pv_pretty_GLOBAL)

char *
DPPP_(my_pv_pretty)(pTHX_ SV *dsv, char const * const str, const STRLEN count,
  const STRLEN max, char const * const start_color, char const * const end_color,
  const U32 flags)
{
    const U8 dq = (flags & PERL_PV_PRETTY_QUOTE) ? '"' : '%';
    STRLEN escaped;

    if (!(flags & PERL_PV_PRETTY_NOCLEAR))
	sv_setpvs(dsv, "");

    if (dq == '"')
        sv_catpvs(dsv, "\"");
    else if (flags & PERL_PV_PRETTY_LTGT)
        sv_catpvs(dsv, "<");

    if (start_color != NULL)
        sv_catpv(dsv, D_PPP_CONSTPV_ARG(start_color));

    pv_escape(dsv, str, count, max, &escaped, flags | PERL_PV_ESCAPE_NOCLEAR);

    if (end_color != NULL)
        sv_catpv(dsv, D_PPP_CONSTPV_ARG(end_color));

    if (dq == '"')
	sv_catpvs(dsv, "\"");
    else if (flags & PERL_PV_PRETTY_LTGT)
        sv_catpvs(dsv, ">");

    if ((flags & PERL_PV_PRETTY_ELLIPSES) && escaped < count)
	sv_catpvs(dsv, "...");

    return SvPVX(dsv);
}

#endif
#endif

#ifndef pv_display
#if defined(NEED_pv_display)
static char * DPPP_(my_pv_display)(pTHX_ SV * dsv, const char * pv, STRLEN cur, STRLEN len, STRLEN pvlim);
static
#else
extern char * DPPP_(my_pv_display)(pTHX_ SV * dsv, const char * pv, STRLEN cur, STRLEN len, STRLEN pvlim);
#endif

#ifdef pv_display
#  undef pv_display
#endif
#define pv_display(a,b,c,d,e) DPPP_(my_pv_display)(aTHX_ a,b,c,d,e)
#define Perl_pv_display DPPP_(my_pv_display)

#if defined(NEED_pv_display) || defined(NEED_pv_display_GLOBAL)

char *
DPPP_(my_pv_display)(pTHX_ SV *dsv, const char *pv, STRLEN cur, STRLEN len, STRLEN pvlim)
{
    pv_pretty(dsv, pv, cur, pvlim, NULL, NULL, PERL_PV_PRETTY_DUMP);
    if (len > cur && pv[cur] == '\0')
	sv_catpvs(dsv, "\\0");
    return SvPVX(dsv);
}

#endif
#endif

#endif /* _P_P_PORTABILITY_H_ */

/* End of File ppport.h */
