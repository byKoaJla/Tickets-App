//
// Created by Denis on 15.05.2024.
//


#include "styles.hpp"

#include <iomanip>
#include <string>
#include <iostream>
#include <utils.hpp>

using namespace std;
namespace Styles {
    void bPrintH( const string &str) {
        cout << endl;
        cout << "+" << setfill('-')<< setw(Utils::strlen(str)+3) << "+" << endl;
        cout << "| " << str << " |" << endl;
        cout << "+" << setfill('-')<< setw(Utils::strlen(str)+3) << "+" << endl;
        cout << endl;
    }

    void user_interface(const string &n_line) {
        cout << endl;
        cout << n_line;
    }

    void ticket_header() {
        cout << left << setfill(' ') << setw(15) << "Номер"
                  << setw(17) << "День"
                  << setw(14) << "Время"
                  << setw(29) << "Направление"
                  << right << setw(20) << "Свободные места" << endl;
        cout << string(66, '-') << endl;
    }
    void reseved_header() {
        cout << left << setfill(' ') << setw(15) << "Номер"
                  << setw(16) << "День"
                  << setw(15) << "Время"
                  << setw(30) << "Направление"
                  << setw(20) << "Зарезерв. места"
                  << right << setw(30) << "Номер телефона"<< endl;
        cout << string(85, '-') << endl;
    }

    string pLogo() {
        const string logo =
        "    /$$$$$$  /$$   /$$                      /$$   /$$\n"
        "   /$$__  $$|__/  | $$                     | $$$ | $$\n"
        "   | $$  \\__/ /$$ /$$$$$$   /$$   /$$      | $$$$| $$\n"
        "   | $$      | $$|_  $$_/  | $$  | $$      | $$ $$ $$\n"
        "   | $$      | $$  | $$    | $$  | $$      | $$  $$$$\n"
        "   | $$    $$| $$  | $$ /$$| $$  | $$      | $$\\  $$$\n"
        "   |  $$$$$$/| $$  |  $$$$/|  $$$$$$$      | $$ \\  $$\n"
        "    \\______/ |__/   \\___/   \\____  $$      |__/  \\__/\n"
        "                            /$$  | $$                \n"
        "                           |  $$$$$$/                \n"
        "                           \\______/                  \n";

        return logo;
    }
    string auth_logo() {
        const string logo =
            "\n"
        "\n"
        "\n"
        "                                                                                                         uB\n"                                                                           "                                                                                                       }C}b\n"
        "                                                                                                     .z}f0~\n"
        "                                 ^:Xk(tOm:` '                                  ' '                   tMbXb:    .UI\n"
        "                                _&*m-\".,~ic#zx(                          !~c0Xq/dYnx],               |p&UX\"   '0J,\n"
        "                             .C*B:',JMx'oh**@&%M'                     t~k]!\":^'<l;r;>XJ>         I~  18%\".   Cfn/ \n"
        "                            .mBU:>.ll}L@dI(u@$$$@%X{-]-,i\" ..    '~]ct1'...`C{,aWqC_LtxUX)<.      /- )q.'' :Y|*)~\n"
        "                           Iv1^...:{LYM$@x?O@$$$$@@*){[?_|WWY~l'YB@@hwYlI>cL)o@@&XI'..`?))[]I      z`t?O<.Xf[0[r\n"
        "                          >)U@%v'.i|*n&@@@@@@B&w^..'.....\")......',>B@@@@Um@$$$&m&i.....''uY;^      oW_.^{[]1{]L\n"
        "                          ^cZ)nn|.;vq@@$$$@80~`.........\"t.........,.uOB@@@$$$$%%o|;,..'_00ac^,     i_  v[][[](:\n"
        "                          .f&?);..'!vOY#$@@O`...........l^...........\"!k@$$$$$$@@%t....''\"n8ah+     b  L{[}1|]B\n"
        "      a].                 ,<+jf,....ta8$@*]'......................^>}~x:%M@$$@@8Mk[-+<'.'CfC0tx`   U,  p]]x)[j[ t-\n"
        "      _cJ~           cI  .?|Uu<i'...!LYo@Z..............................nd@$$$%J[rJi`....+(pXX     c  ^][Xw|v) <xu\n"
        "      '][|c'        |q:   >{ck[',ic_.IO@d'..'^.....`'']............'\"^-1oZ%@$U)rt++fq>..^!ZQWL^    .u 'UCkfq  'q]h\n"
        "       {10fQ.      C{C;   _|CBCz!'...lpM[....,^'`_]l<n_?[\"`....'/,|-.;[UUj~@@@Un}`'.'<j\"JdkLh(     m'>|@z+   1U)(a\n"
        "        h|COx:    'x]uI    }8ckO~'...IoJ..1:.^xU1rJ'^X~Ym/J{t\"?(i-j,-~.''^`^@Btw{>.....'',;iu^    n)k@a    IZzft|d\n"
        "        j[xfm)<   z]][XI.!]')?rYqf?..<0>....{>YhJ(.[c&@Xi><atmQho#hJ|;;`I0Z1zWOJ(I....i[Xv8*>   :rCqLQU@t dCtC/LCI\n"
        "         (]}[)z:  r[][]#n([`  :Ja@|+.<1.'f_'0xfbQLWL@$$$$@YzXXx,'I';ndJ,'?p.zkW<\".I!~`;1{xX:^ [u*/Uo8x>  u|/oa)Mv'\n"
        "         q[[n1[u   /]]]0{]n,   (?<qZ%L<.cvikk8JO[o;h@$$$$@{mQLcL&%jrJ{{Y1|(YXd@a'.:t#Bx-Y 'rM/CdropI    ?J##Cu#i\n"
        "         *]][/]/<  #[|q}nk&      \"?l*m....'cY@/i{_($$$$$$@n.'.@@@Uz[kdY|zx\".cbB@hrx{un(! ?J]XbMWX_  '1wxhj?+,\n"
        "         k]]]({fm   8&([(j@        +#_{'..'\"``..z,*$$$$$$B#r>.'>::::UjJ||<',b*$o\"\"+\" ^  C{J/Omm;. 1j1ck;\n"
        "         _/f0j0t[i  uu])Y1B        'dCm>.,_j[cY1$$$$$$$$$@Jr/?i`?fUfrt!<]l:Y0@@w      'rcm%&Bw  'vpLmx\"`)0qfvnd{!\n"
        "  ,/.    ;Xnjnwfcz >c[]}|]C:  ^L_    %#{.';`~Yv[$$$$$$$$$@0kbbJY1<:,'I"".'nuBBp,      cJnB%8J  ;&,iZaOdkWWbwC{]](nUl\n"
        "   (Wi    <t]dk%pz &]]]L]][v  :vx    YB]!l`_r_i'CxW$$$@Qn%...+ULni...!L/lJ*B@@@J     r1rp0ov\" .O@Z;       qrLqmwkCdw>\n"
        "    1nJ_.   rcc&oz}}]]]h]]]Z  ILc'   :pB@z{,:jljZwom@@rWB/;nx.1>^>,]'I)k0Q&@@@@%r.  _xBWuBn< uab.\n"
        "     \"wU#.    Iv@zJ]][}(]]1x  C[]h    <a8or(Ix!@z':;;;vqvI""w'j|^'?X}U|oh@@+,{q@%1 `cJm(hqZQB[^\n"
        "      >p0LU\"    qUa]]]b}XtB. z}]]8.   Ib$$$u(+_#),.........,C@wj][t0*&*MBd-..ick@Z {Y(uk*@J^\n"
        "       lwLdb.   ;Uk[{100|ct r([][|x  m@$$$$$$@hWqu|(,(])l}~U{?(QpC{bo@@p'...`_+p@@ww](%8@]\n"
        "         MaQmC'  |j#an}kUp !t]][[[Qzai&%$$$$$$$$$@%@@@@@8BYpQ@@@$@@$%&C(..''\"-*&w$%?OJ@@m   '.          ',IJ&O,\n"
        "         ^vczbUt  u&Q8q}Q] +v]1u]jm+`_h@$$$$$$$$$$$$$$$$$$$@$$$$$@@bB]'....I(?u8@@?f&f*BUJ@@@$BJl    <XOoYxhhO#f\n"
        "   .zLtJ\" .[LLdUJnuurzXh/; I)]}nbk^..QcB@@$$$$$$$@@d@8@@@@@@@@M@@wu0.`....'`/hC$@btxj)@$@%rxiC@@$Z.0&*o%B@0:\".\n"
        "      [c[}Yr+jOp0mkp*kUX   I))h*fn...<rO@@MB$$$$$@Q+/q+Q|fnYxL}uv?{>....../i[X%$@u&Um#@$BC?1i`+OL@&c#wz\n"
        "       IZ]]][f\"xc .*UY`    -h(~nv'...^t]ma@$$$$$$$$8('r::]^l'~!\"(!!;.....`t%BB$&mUp*Um@$@$@0,'<>j@@&_\n"
        "         0[{]n) `Y{&jf   \"Wm?k0@?:/'.`l,mLf{i1qa&&B$@@_`.''...''.'`.....iCM$@8udQc1or}zd8$*b1_mQ@@/ \n"
        "         \"zQuraI  1qb1'^U(.|lf@U`..<}:``'+.|i'<i>)r0@@@M)'...,!.......'j#%@BqpCuY0qjp%@@$$@$$@@@@dI       `[xxrXC!\n"
        "  'xq){)UCYn88Xk   <uwl*(''-8$@z..:)!.''kLz(a_!..+uUYw8@@%;.(.,,.!l;.Y/o@#jL)(YLnkv8&$$$$$$$$$$@t    \"0Lt)v8aj0Wb,\n"
        " 1vQvcz1t}jpj0dB#I  kZt.'rxhB@@Y'.+<:CZ|O/,'!`'z(xLuQ0|tm8@$@djJ{x)1b@@k1xjUzvhpOW&@$$$$$$@@Wqu,   <rpn%bCqwz;\n"
        "      `++ndXrQw!`n] Wj',U}~v8@$Z:.{xIJ)?//|X<I>Xt1vYtdOpdc/f?,'',[[[[tqd&XxuJC1*BB$$$$$$@O''  .|0kmkkUw*(;\n"
        "               \"p':Bz`.'-qmB$$$Q\"Uru\";!,j]<x%XX)aCcB%BL&*/{/.......i/0o#Mmddh@@@@$$$$@@@@BQ#@Lmx)LW@8Y`\n"
        "        ~j;       Z).'fk@8@@$$$B{`>px|r1wvn+)/d|xQxjz1mxXhqu,........._x}jk@@@@@@8qCCc([{Cxznp%*@kx\"\n"
        "         |jUZ    <o;}p@@W8;1ZB@%8Y-db?CYOUw+u~mhkmQpx*>?[qp/}'.......''l@BBMBM|?-[(wZ(bx[fW%BY:^\n"
        "         .)|[tx' tLOm['.......?Q8$obLxfaLL)~ft-1zr|x[1*1f{ub+^;:`''.;>{/!%@oL1rxxxxcuxd@$$l              .i-1UO/ \n"
        "          \"z]]]| /8\"...........it)m@$BJ0%q/Jz1fvcLCrjOfj/o0i',\"+!?Lkh/0@oM@do@$$$$$$$$$$@@           \"cYjj}(r\n"
        "           x}[]]{cv.............l'lLoB@W$@B%OJ%o*#ha8adWpWkB@)B0p@$$@@@$$@@$$$$$$$$$$$$$@%       .lkr[[)Z[}Z\n"
        "            8[]]Uj'..';...'`,'......l)pb$@$$$$@@@@@$@$@$@@@@@$$$$$$$$$$$$$$$$$$$$$$$$$$@@      1fu]x(CL)}/r\n"
        " .UdZu>      w[[W-.'.}01,ic[!'.;,~''\"?Y+'a@$$$@@@Qlt@$$@@@@@@@@@$$$$$$$$$$$$$$$$$$$$$@@@?   'k|[]]]d{()1rt\n"
        "   ?0j1JrQuI  |Wo\",I;~0Lct?zJrx>,zl}1{{/cmaB$BplIm$$$$$@bkmcdOJ%#$@Q1a$$$$$$$$$$$$$$$@Z,  /v[]]][/t]]][v}\n"
        "     ^/nj0mtU^ 0o^.X?>rLX(I|n?|ZQ]<u&(imUL0%o:..:l~|8$@OZtvQZ@C@$Bd1[&$$$$$$BLM@$$@b}I  'q)f}]]z|ux[]ut\n"
        "        [XJd|?I.W]'ql.Q]u/qf}C]~_>/JW_lilci''...Im@B@@h?}OB&n8@@$MO-Jh&$$$$$M?         'u[Jj)CuJJ|{/w\n"
        "          <L0aY,Mv`Y{,'J*ui+vqj|0Ow,x[}?}>^....I`}uB$@#o0bUYmM$@@@@%i}o$$$$$bI        .}YXJJ(U1[Uj_\n"
        "            '1Lw!a<m()>~n1zpuXvhZ}1rm]<Iml[*...x8@$$$$@J(?bdo$$$$Mn1:1$$$$$${'        Mbf[Uao)\"^\n"
        "               1,u@U]~\",(x0&%X+b(w<up(j\"(0CZ;^tc*@$$@BbXQChW@$$@@%L]xo$$$$$%]     ,(wZx\n"
        "                 ;q@{j}_[Uic#C]mum1Cd|vXY1tf<LM8$$$$@*jvM#@$$$$@@BW8$$$$$$*< .?0Yjx)/vOQj(ZaJ/nI\n"
        "                  v%Bt0hfZdJa@nXLzZm}JpMBY&$M0@$$@%OXd0dm@$$$$$$$$$$$$$$@8#o|^',Il,' fM*jkbw#C}}1tu>'''..\n"
        "                    bWoW&*Yv/&@%B#Bk8M%@$@@$$$$$&LwM&q*J@$$$$$$$$$$$$$@@mnxnc0kpYY{/xr:<ZudUQZZ)UXrr]1X].\n"
        "                    .X@$$$$$%B$$$$$$$$$$$$$@@@@BpMp8%qW@$$$$$$$$$$$@@j\".    .~1ocb}[[]}v/I*Xb|u|]]j*n\"\n"
        "                      \"M@$$$$$$@*k&@@@8m##qu%wopzuk&Co$$$$$$$$$$$$$L           YnJULJx{][m~  \"iI\n"
        "                       ']b$$$@#jJowbBxUUfp&Xdqq%$@$$$$$$$$$$$$$$$@%Qun0d#Xnnrz- .~_t)|)r/Yhf.\n"
        "                          ,oL)WLj*Y[YLYWOCO@Wb&*@@$$$$$$$$$$$$$B#  ZaL`!vJz&Jzm0Ll\n"
        "                       ^zkCQLY?}jCXLdY}r/uZQB8*@$$$$$$$$$$$$$@U`  -u%uJc`tXJc[]][}hQi\n"
        "                     (*#Y#/(??cf?vp[O)L]#bB@8h@$$$$$$$$$$$$@k,   \"|[v{[[d \"J<!<^,^\n"
        "                  <0&ZCCUvj-1k[UaCvYw?tpa*MBB$$$$$$$$$$$$@h?     IL][x]]v.\n"
        "               .0#OfkLp|Yf?0XmOYv0Q|Udma&BM8@$$$$$$$$$BZ{'       I0][q]]1_\n"
        "            :|%W)u#|Cq|0]w[Qu}b(r]Cm#&#81%#8$BB&M#pc,^           .|f[YfX1f \n"
        "         jmBCccUzXUQtu{c/vn1YCYjma*W*@*M%.                         /vxcLQ~'\n"
        "         ^IQ}/Q|az}]wLt1Wn-p|]*&%@UO@(h@                            '/C}[[]\n"
        "            ,|u???]C/QcZ(foLmWB&C0JmWk@}                                <UOO|\n"
        "              .\"-?-?uujcC)dd&m&8@@knrJo-\n"
        "                  l_fqY?{d%obBBW8%k]\n"
        "                     ^I~zc0&M%@d!\n"
        "                          .^.:,\n"
        "\n"
        "\n";
        return logo;
    }
}