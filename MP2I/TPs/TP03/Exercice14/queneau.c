/* affiche un des cent mille milliards de poèmes de Raymond Queneau */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* vers[14][10] = {
    {
        "Le roi de la pampa retourne sa chemise",
        "Le cheval Parthénon s'énerve sur sa frise",
        "Le vieux marin breton de tabac prit sa prise",
        "C'était à cinq o'clock que sortait la marquise",
        "Du jeune avantageux la nymphe était éprise",
        "Il se penche il voudrait attraper sa valise",
        "Quand l'un avecque l'autre aussitôt sympathise",
        "Lorsqu'un jour exalté l'aède prosaïse",
        "Le marbre pour l'acide est une friandise",
        "Lorsque tout est fini lorsque l'on agonise"
    },
    {
        "pour la mettre à sécher aux cornes des taureaux",
        "depuis que lord Elgin négligea ses naseaux",
        "pour du fin fond du nez exciter les arceaux",
        "pour consommer un thé puis des petits gâteaux",
        "snob un peu sur les bords des bords fondamentaux",
        "que convoitait c'est sûr une horde d'escrocs",
        "se faire il pourrait bien que ce soit des jumeaux",
        "pour déplaire au profane aussi bien qu'aux idiots",
        "d'aucuns par dessus tout prisent les escargots",
        "lorsque le marbrier astique nos tombeaux"
    },
    {
        "le cornédbîf en boîte empeste la remise",
        "le Turc de ce temps-là pataugeait dans sa crise",
        "sur l'antique bahut il choisit sa cerise",
        "le chauffeur indigène attendait dans la brise",
        "une toge il portait qui n'était pas de mise",
        "il se penche et alors à sa grande surprise",
        "la découverte alors voilà qui traumatise",
        "la critique lucide aperçoit ce qu'il vise",
        "sur la place un forain de feu se gargarise",
        "des êtres indécis vous parlent sans franchise"
    },
    {
        "et fermentent de même et les cuirs et les peaux",
        "il chantait tout de même oui mais il chantait faux",
        "il n'avait droit qu'à une et le jour des Rameaux",
        "elle soufflait bien fort par dessus les côteaux",
        "des narcisses on cueille ou bien on est des veaux",
        "il ne trouve aussi sec qu'un sac de vieux fayots",
        "on espère toujours être de vrais normaux",
        "il donne à la tribu des cris aux sens nouveaux",
        "qui sait si le requin boulotte les turbots?",
        "et tout vient signifier la fin des haricots"
    },
    {
        "Je me souviens encor de cette heure exeuquise",
        "Le cheval Parthénon frissonnait sous la bise",
        "Souvenez-vous amis de ces îles de Frise",
        "On était bien surpris par cette plaine grise",
        "Quand on prend des photos de cette tour de Pise",
        "Il déplore il déplore une telle mainmise",
        "Et pourtant c'était lui le frère de feintise",
        "L'un et l'autre a raison non la foule insoumise",
        "Du voisin le Papou suçote l'apophyse",
        "On vous fait devenir une orde marchandise"
    },
    {
        "les gauchos dans la plaine agitaient leurs drapeaux",
        "du client londonien où s'ébattent les beaux",
        "où venaient par milliers s'échouer les harenceaux",
        "quand se carbonisait la fureur des châteaux",
        "d'où Galilée jadis jeta ses petits pots",
        "qui se plaît à flouer de pauvres provinciaux",
        "qui clochard devenant jetait ses oripeaux",
        "le vulgaire s'entête à vouloir des vers beaux",
        "que n'a pas dévoré la horse de mulots?",
        "on prépare la route aux penseurs sépulcraux"
    },
    {
        "nous avions aussi froids que nus sur la banquise",
        "il grelottait le pauvre au bord de la Tamise",
        "nous regrettions un peu ce tas de marchandise",
        "un audacieux baron empoche toute accise",
        "d'une étrusque inscription la pierre était incise",
        "aller à la grand ville est bien une entreprise",
        "un frère même bas est la part indécise",
        "l'un et l'autre ont raison non la foule imprécise",
        "le gourmet en salade avale la cytise",
        "de la mort on vous greffe une orde bâtardise"
    },
    {
        "lorsque pur nous distraire y plantions nos tréteaux",
        "quand les grêlons fin mars mitraillent les bateaux",
        "lorsqu'on voyait au loin flamber les arbrisseaux",
        "lorsque vient le pompier avec ses grandes eaux",
        "les Grecs et les Romains en vain cherchent leurs mots",
        "elle effraie le Berry comme les Morvandiaux",
        "que les parents féconds offrent aux purs berceaux",
        "à tous n'est pas donné d'aimer les chocs verbaux",
        "l'enfant pur aux yeux bleus aime les berlingots",
        "la mite a grignoté tissus os et rideaux"
    },
    {
        "Du pôle à Rosario fait une belle trotte",
        "La Grèce de Platon à coup sûr n'est point sotte",
        "On sèche le poisson dorade ou molve lotte",
        "Du Gange au Malabar le lord anglais zozotte",
        "L'esprit souffle et resouffle au-dessus de la botte",
        "Devant la boue urbaine on retrousse sa cotte",
        "Le généalogiste observe leur bouillotte",
        "Le poète inspiré n'est point un polyglotte",
        "Le loup est amateur de coq et de cocotte",
        "Le brave a beau crier ah cré nom saperlotte"
    },
    {
        "aventures on eut qui s'y pique s'y frotte",
        "on comptait les esprits acérés à la hotte",
        "on sale le requin on fume à l'échalotte",
        "comme à Chandernagor le manant sent la crotte",
        "le touriste à Florence ignoble charibotte",
        "on gifle le marmot qui plonge sa menotte",
        "gratter le parchemin deviendra sa marotte",
        "une langue suffit pour emplir sa cagnotte",
        "le chat fait un festin de têtes de linotte",
        "le lâche peut arguer de sa mine pâlotte"
    },
    {
        "lorsqu'on boit du maté l'on devient argentin",
        "lorsque Socrate mort passait pour un lutin",
        "lorsqu'on revient au port en essuyant un grain",
        "le colonel s'éponge un blason dans la main",
        "l'autocar écrabouille un peu d'esprit latin",
        "lorsqu'il voit la gadoue il cherche le purin",
        "il voudra retrouver le germe adultérin",
        "même s'il prend son sel au celte c'est son bien",
        "le chemin vicinal se nourrit de crottin",
        "le croque-morts sont là pour se mettre au turbin"
    },
    {
        "L'Amérique du Sud séduit les équivoques",
        "Sa sculpture est illustre et dans le fond des coques",
        "Enfin on vend le tout homards et salicoques",
        "Ne fallait pas si loin agiter ses breloques",
        "Les rapports transalpins sont-ils biunivoques?",
        "On regrette à la fin les agrestes bicoques",
        "Frère je te comprends si parfois tu débloques",
        "Barde que tu me plais toujours tu soliloques",
        "On a bu du pinard à toutes les époques",
        "Cela considérant ô lecteur tu suffoques"
    },
    {
        "exaltent l'espagnol les oreilles baroques",
        "on transporte et le marbre et débris et défroques",
        "on s'excuse il n'y a ni baleines ni phoques",
        "les Indes ont assez sans ça de pendeloques",
        "les banquiers d'Avignon changent-ils les baïoques?",
        "on mettait sans façon ses plus infectes loques",
        "frère je t'absoudrai si tu m'emberlucoques",
        "tu me stupéfies plus que tous les ventriloques",
        "grignoter des bretzels distrait bien des colloques",
        "comptant tes abattis lecteur tu te disloques"
    },
    {
        "si la cloche se tait et son terlintintin",
        "si l'Europe le veut l'Europe ou son destin",
        "le mammifère est roi nous sommes son cousin",
        "l'écu de vair ou d'or ne dure qu'un matin",
        "le Beaune et le Chianti sont-ils le même vin?",
        "mais on n'aurait pas vu le métropolitain",
        "la gémellité vraie accuse son destin",
        "le métromane à force incarne le devin",
        "mais rien ne vaut grillé le morceau de boudin",
        "toute chose pourtant doit avoir une fin"
    }
};


int main(){
    srand(time(NULL));
    int vers_rand;
    for (int i = 0; i < 14; i++) {
        vers_rand = rand() % 10;
        printf("%s\n", vers[i][vers_rand]);
        if (i == 3 || i == 7 || i == 10) {
            /* mise en forme du sonnet : il faut des sauts de lignes entre
             * les deux quatrains, entre le deuxième quatrain et le premier
             * tercet, et entre les deux tercets */
            printf("\n");
        }
    }
    return 0;
}
