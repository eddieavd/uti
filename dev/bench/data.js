window.BENCHMARK_DATA = {
  "lastUpdate": 1706345588141,
  "repoUrl": "https://github.com/eddieavd/uti",
  "entries": {
    "uti benchmark": [
      {
        "commit": {
          "author": {
            "email": "edhemavdagic@gmail.com",
            "name": "Edhem Avdagic",
            "username": "eddieavd"
          },
          "committer": {
            "email": "edhemavdagic@gmail.com",
            "name": "Edhem Avdagic",
            "username": "eddieavd"
          },
          "distinct": true,
          "id": "93c7c4200bdeb80897a51c951529829d6031e813",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T09:40:07+01:00",
          "tree_id": "f9d9efca1cb44e0bf0eb8da73d00104bf96f679b",
          "url": "https://github.com/eddieavd/uti/commit/93c7c4200bdeb80897a51c951529829d6031e813"
        },
        "date": 1706344945387,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/256",
            "value": 0.30323412400469063,
            "unit": "us/iter",
            "extra": "iterations: 2306816\ncpu: 0.3032136503301521 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.5030015492022174,
            "unit": "us/iter",
            "extra": "iterations: 1395557\ncpu: 0.5029575287859974 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1024",
            "value": 0.8711577971495031,
            "unit": "us/iter",
            "extra": "iterations: 805756\ncpu: 0.8711020457806085 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2048",
            "value": 2.9058850072598195,
            "unit": "us/iter",
            "extra": "iterations: 239676\ncpu: 2.9056793337672517 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 6.943969126744821,
            "unit": "us/iter",
            "extra": "iterations: 100864\ncpu: 6.943906646573606 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8192",
            "value": 15.01401752805115,
            "unit": "us/iter",
            "extra": "iterations: 46611\ncpu: 15.01328012700865 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16384",
            "value": 31.625101945911613,
            "unit": "us/iter",
            "extra": "iterations: 22149\ncpu: 31.62322000993272 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 125.4944928520397,
            "unit": "us/iter",
            "extra": "iterations: 5596\ncpu: 125.37635811293785 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/65536",
            "value": 296.330509090913,
            "unit": "us/iter",
            "extra": "iterations: 2365\ncpu: 296.2694291754758 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/131072",
            "value": 634.4824538878656,
            "unit": "us/iter",
            "extra": "iterations: 1106\ncpu: 634.3779385171795 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/262144",
            "value": 1405.5861656686486,
            "unit": "us/iter",
            "extra": "iterations: 501\ncpu: 1405.4668662674655 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/256",
            "value": 0.3247031150057631,
            "unit": "us/iter",
            "extra": "iterations: 2157492\ncpu: 0.3246972874059318 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.5415817124528426,
            "unit": "us/iter",
            "extra": "iterations: 1280117\ncpu: 0.5415558890320191 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1024",
            "value": 0.9522069373227507,
            "unit": "us/iter",
            "extra": "iterations: 735817\ncpu: 0.9521915095737105 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2048",
            "value": 1.7626611313143148,
            "unit": "us/iter",
            "extra": "iterations: 397626\ncpu: 1.7626241744755144 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.3710986447339684,
            "unit": "us/iter",
            "extra": "iterations: 208151\ncpu: 3.3708082113465756 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8192",
            "value": 6.55453732127442,
            "unit": "us/iter",
            "extra": "iterations: 106588\ncpu: 6.55438979997749 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16384",
            "value": 12.918404700412985,
            "unit": "us/iter",
            "extra": "iterations: 54208\ncpu: 12.917541691263303 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 25.604030133479693,
            "unit": "us/iter",
            "extra": "iterations: 27345\ncpu: 25.602563539952545 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/65536",
            "value": 51.0065085264542,
            "unit": "us/iter",
            "extra": "iterations: 13722\ncpu: 51.00188747995905 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/131072",
            "value": 102.54267396700267,
            "unit": "us/iter",
            "extra": "iterations: 6849\ncpu: 102.5367060884803 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/262144",
            "value": 204.58960981308695,
            "unit": "us/iter",
            "extra": "iterations: 3424\ncpu: 204.57088200934507 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "edhemavdagic@gmail.com",
            "name": "Edhem Avdagic",
            "username": "eddieavd"
          },
          "committer": {
            "email": "edhemavdagic@gmail.com",
            "name": "Edhem Avdagic",
            "username": "eddieavd"
          },
          "distinct": true,
          "id": "f28d92eacfa3195dc055dd15ebc1af60e91d98ea",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T09:49:35+01:00",
          "tree_id": "7a8467b9e2f9c150c208a5f6e888d5006d1cadce",
          "url": "https://github.com/eddieavd/uti/commit/f28d92eacfa3195dc055dd15ebc1af60e91d98ea"
        },
        "date": 1706345587783,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/256",
            "value": 0.29956942081577637,
            "unit": "us/iter",
            "extra": "iterations: 2318865\ncpu: 0.2995515047232159 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.5017211870730525,
            "unit": "us/iter",
            "extra": "iterations: 1365611\ncpu: 0.5016960906143844 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1024",
            "value": 0.8762867059531709,
            "unit": "us/iter",
            "extra": "iterations: 799087\ncpu: 0.8762173580598862 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2048",
            "value": 2.908890812250405,
            "unit": "us/iter",
            "extra": "iterations: 240320\ncpu: 2.908746671105193 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 8.226365540096065,
            "unit": "us/iter",
            "extra": "iterations: 85096\ncpu: 8.225860204945 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8192",
            "value": 16.332918028969512,
            "unit": "us/iter",
            "extra": "iterations: 42942\ncpu: 16.3327953984444 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16384",
            "value": 32.915714574612565,
            "unit": "us/iter",
            "extra": "iterations: 21263\ncpu: 32.915021398673765 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 130.4749234119842,
            "unit": "us/iter",
            "extra": "iterations: 5510\ncpu: 130.36023593466433 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/65536",
            "value": 300.4196603134263,
            "unit": "us/iter",
            "extra": "iterations: 2361\ncpu: 300.3568403218977 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/131072",
            "value": 639.2710484460742,
            "unit": "us/iter",
            "extra": "iterations: 1094\ncpu: 639.2124314442414 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/262144",
            "value": 1422.5435711382506,
            "unit": "us/iter",
            "extra": "iterations: 492\ncpu: 1422.4241869918699 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/524288",
            "value": 2983.494030043104,
            "unit": "us/iter",
            "extra": "iterations: 233\ncpu: 2983.3326180257554 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1048576",
            "value": 5130.429481751959,
            "unit": "us/iter",
            "extra": "iterations: 137\ncpu: 5130.281751824826 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2097152",
            "value": 8805.515924051104,
            "unit": "us/iter",
            "extra": "iterations: 79\ncpu: 8805.026582278488 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4194304",
            "value": 15683.268477272608,
            "unit": "us/iter",
            "extra": "iterations: 44\ncpu: 15682.868181818207 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8388608",
            "value": 21524.491937499944,
            "unit": "us/iter",
            "extra": "iterations: 32\ncpu: 21524.15624999998 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16777216",
            "value": 34509.35864999849,
            "unit": "us/iter",
            "extra": "iterations: 20\ncpu: 34507.29499999996 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/256",
            "value": 0.3156923405459829,
            "unit": "us/iter",
            "extra": "iterations: 2214949\ncpu: 0.31568221209608 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.5059343216307897,
            "unit": "us/iter",
            "extra": "iterations: 1387504\ncpu: 0.505839190373505 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1024",
            "value": 0.8819126882987518,
            "unit": "us/iter",
            "extra": "iterations: 801187\ncpu: 0.8818516775734003 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2048",
            "value": 1.5895667347636773,
            "unit": "us/iter",
            "extra": "iterations: 441037\ncpu: 1.5895108573657089 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.016100146896062,
            "unit": "us/iter",
            "extra": "iterations: 232818\ncpu: 3.015862605125039 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8192",
            "value": 5.8385347047558405,
            "unit": "us/iter",
            "extra": "iterations: 120070\ncpu: 5.83805530107437 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16384",
            "value": 11.43163940538646,
            "unit": "us/iter",
            "extra": "iterations: 61149\ncpu: 11.431097810266733 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 22.806696331852734,
            "unit": "us/iter",
            "extra": "iterations: 30833\ncpu: 22.806126552719395 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/65536",
            "value": 45.29943909366786,
            "unit": "us/iter",
            "extra": "iterations: 15491\ncpu: 45.29715318572069 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/131072",
            "value": 90.22026636598146,
            "unit": "us/iter",
            "extra": "iterations: 7760\ncpu: 90.21452319587657 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/262144",
            "value": 180.35041850792325,
            "unit": "us/iter",
            "extra": "iterations: 3847\ncpu: 180.34554198076484 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/524288",
            "value": 360.69935239567775,
            "unit": "us/iter",
            "extra": "iterations: 1941\ncpu: 360.68815043791966 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1048576",
            "value": 720.7883952772073,
            "unit": "us/iter",
            "extra": "iterations: 974\ncpu: 720.7681724846005 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2097152",
            "value": 1445.8098559670493,
            "unit": "us/iter",
            "extra": "iterations: 486\ncpu: 1445.7218106995922 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4194304",
            "value": 2879.376370370476,
            "unit": "us/iter",
            "extra": "iterations: 243\ncpu: 2879.193004115233 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8388608",
            "value": 9093.912582278635,
            "unit": "us/iter",
            "extra": "iterations: 79\ncpu: 9093.215189873432 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16777216",
            "value": 19900.25520000082,
            "unit": "us/iter",
            "extra": "iterations: 35\ncpu: 19898.745714285684 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/256",
            "value": 1.8128399171141378,
            "unit": "us/iter",
            "extra": "iterations: 386556\ncpu: 1.8127989217603677 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/512",
            "value": 3.4747371345988065,
            "unit": "us/iter",
            "extra": "iterations: 201354\ncpu: 3.4746203204306747 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1024",
            "value": 6.787442900366584,
            "unit": "us/iter",
            "extra": "iterations: 103118\ncpu: 6.7872835004557395 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/2048",
            "value": 13.273402508205177,
            "unit": "us/iter",
            "extra": "iterations: 52707\ncpu: 13.2731174227332 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/4096",
            "value": 27.42527216262125,
            "unit": "us/iter",
            "extra": "iterations: 26565\ncpu: 27.42464897421404 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/8192",
            "value": 55.14329178492753,
            "unit": "us/iter",
            "extra": "iterations: 12684\ncpu: 55.142210659097934 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/16384",
            "value": 110.2623660544612,
            "unit": "us/iter",
            "extra": "iterations: 6316\ncpu: 110.25657061431231 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/32768",
            "value": 219.32249452269735,
            "unit": "us/iter",
            "extra": "iterations: 3195\ncpu: 219.3188106416264 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/65536",
            "value": 418.4147467066066,
            "unit": "us/iter",
            "extra": "iterations: 1670\ncpu: 418.4044910179628 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/131072",
            "value": 833.2584290822213,
            "unit": "us/iter",
            "extra": "iterations: 839\ncpu: 833.2224076281353 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/262144",
            "value": 1683.4619522672317,
            "unit": "us/iter",
            "extra": "iterations: 419\ncpu: 1683.3331742243513 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/524288",
            "value": 8970.833311688883,
            "unit": "us/iter",
            "extra": "iterations: 77\ncpu: 8969.977922077895 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1048576",
            "value": 15752.205222222276,
            "unit": "us/iter",
            "extra": "iterations: 45\ncpu: 15751.399999999985 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/256",
            "value": 1.1091989529127733,
            "unit": "us/iter",
            "extra": "iterations: 632612\ncpu: 1.109202164992133 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/512",
            "value": 2.1030464390150465,
            "unit": "us/iter",
            "extra": "iterations: 333082\ncpu: 2.1030524015107495 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1024",
            "value": 4.088093820454493,
            "unit": "us/iter",
            "extra": "iterations: 171210\ncpu: 4.088108171251681 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/2048",
            "value": 8.142928687768274,
            "unit": "us/iter",
            "extra": "iterations: 87797\ncpu: 8.142960465619494 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/4096",
            "value": 15.913710710416183,
            "unit": "us/iter",
            "extra": "iterations: 44312\ncpu: 15.912991966058897 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/8192",
            "value": 31.836240718019567,
            "unit": "us/iter",
            "extra": "iterations: 22005\ncpu: 31.835414678482074 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/16384",
            "value": 64.90262526926972,
            "unit": "us/iter",
            "extra": "iterations: 10677\ncpu: 64.89850145171881 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/32768",
            "value": 125.64861318052134,
            "unit": "us/iter",
            "extra": "iterations: 5584\ncpu: 125.64272922636076 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/65536",
            "value": 249.9814694096625,
            "unit": "us/iter",
            "extra": "iterations: 2795\ncpu: 249.95610017889027 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/131072",
            "value": 490.09853953813854,
            "unit": "us/iter",
            "extra": "iterations: 1429\ncpu: 490.0691392582189 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/262144",
            "value": 1010.7864267425452,
            "unit": "us/iter",
            "extra": "iterations: 703\ncpu: 1010.7229018492104 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/524288",
            "value": 7895.6303176469455,
            "unit": "us/iter",
            "extra": "iterations: 85\ncpu: 7895.141176470588 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1048576",
            "value": 13466.962442308273,
            "unit": "us/iter",
            "extra": "iterations: 52\ncpu: 13466.265384615339 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/256",
            "value": 0.16993172654837854,
            "unit": "us/iter",
            "extra": "iterations: 4113722\ncpu: 0.1699313176729011 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/512",
            "value": 0.34405784626518726,
            "unit": "us/iter",
            "extra": "iterations: 2033528\ncpu: 0.34404453737543933 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/1024",
            "value": 0.6631386150796889,
            "unit": "us/iter",
            "extra": "iterations: 1056494\ncpu: 0.6631066527590306 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/2048",
            "value": 1.2964968249795603,
            "unit": "us/iter",
            "extra": "iterations: 540154\ncpu: 1.2965021086578956 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/4096",
            "value": 2.5637987950264773,
            "unit": "us/iter",
            "extra": "iterations: 273035\ncpu: 2.5637255296940133 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/8192",
            "value": 5.1138569102841,
            "unit": "us/iter",
            "extra": "iterations: 136977\ncpu: 5.1137512137074275 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/16384",
            "value": 10.355144337088207,
            "unit": "us/iter",
            "extra": "iterations: 67377\ncpu: 10.35427519776778 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/32768",
            "value": 20.678840614838908,
            "unit": "us/iter",
            "extra": "iterations: 33830\ncpu: 20.67788353532368 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/65536",
            "value": 41.3779154064257,
            "unit": "us/iter",
            "extra": "iterations: 16928\ncpu: 41.376429584120764 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/131072",
            "value": 82.9567972732696,
            "unit": "us/iter",
            "extra": "iterations: 8435\ncpu: 82.95508002371066 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/262144",
            "value": 166.28108040797034,
            "unit": "us/iter",
            "extra": "iterations: 4216\ncpu: 166.28152277039953 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/524288",
            "value": 332.1792861889089,
            "unit": "us/iter",
            "extra": "iterations: 2107\ncpu: 332.1720455624135 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/1048576",
            "value": 664.4651450236697,
            "unit": "us/iter",
            "extra": "iterations: 1055\ncpu: 664.4673933649398 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/2097152",
            "value": 1330.4318802281293,
            "unit": "us/iter",
            "extra": "iterations: 526\ncpu: 1330.3682509505597 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/4194304",
            "value": 2661.345680608307,
            "unit": "us/iter",
            "extra": "iterations: 263\ncpu: 2661.271102661609 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/8388608",
            "value": 7570.812419354903,
            "unit": "us/iter",
            "extra": "iterations: 93\ncpu: 7570.112903225944 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/16777216",
            "value": 15892.00361363587,
            "unit": "us/iter",
            "extra": "iterations: 44\ncpu: 15891.609090909304 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/256",
            "value": 0.20278375197546042,
            "unit": "us/iter",
            "extra": "iterations: 3405534\ncpu: 0.20276734867424226 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/512",
            "value": 0.3893340969494283,
            "unit": "us/iter",
            "extra": "iterations: 1798897\ncpu: 0.38932434708601704 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/1024",
            "value": 0.7331942250328708,
            "unit": "us/iter",
            "extra": "iterations: 952421\ncpu: 0.733160545599061 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/2048",
            "value": 1.4302950264498542,
            "unit": "us/iter",
            "extra": "iterations: 485448\ncpu: 1.43022713040326 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/4096",
            "value": 2.8321936894480038,
            "unit": "us/iter",
            "extra": "iterations: 247205\ncpu: 2.832114641694114 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/8192",
            "value": 5.644403160216311,
            "unit": "us/iter",
            "extra": "iterations: 124675\ncpu: 5.644269500701798 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/16384",
            "value": 11.23534389554472,
            "unit": "us/iter",
            "extra": "iterations: 62266\ncpu: 11.234803905823314 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/32768",
            "value": 22.478338302717116,
            "unit": "us/iter",
            "extra": "iterations: 31191\ncpu: 22.477769228302872 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/65536",
            "value": 44.872249421444174,
            "unit": "us/iter",
            "extra": "iterations: 15556\ncpu: 44.872390074569964 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/131072",
            "value": 89.93234214598394,
            "unit": "us/iter",
            "extra": "iterations: 7754\ncpu: 89.92933969563975 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/262144",
            "value": 180.11643346203078,
            "unit": "us/iter",
            "extra": "iterations: 3885\ncpu: 180.1131788931776 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/524288",
            "value": 360.75154704369646,
            "unit": "us/iter",
            "extra": "iterations: 1945\ncpu: 360.71989717223727 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/1048576",
            "value": 720.9744506172816,
            "unit": "us/iter",
            "extra": "iterations: 972\ncpu: 720.9602880658318 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/2097152",
            "value": 1445.4216584361716,
            "unit": "us/iter",
            "extra": "iterations: 486\ncpu: 1445.3598765432166 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/4194304",
            "value": 2880.9370785123906,
            "unit": "us/iter",
            "extra": "iterations: 242\ncpu: 2880.85702479338 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/8388608",
            "value": 7939.161932584059,
            "unit": "us/iter",
            "extra": "iterations: 89\ncpu: 7939.065168539252 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/16777216",
            "value": 16701.459619046742,
            "unit": "us/iter",
            "extra": "iterations: 42\ncpu: 16700.099999999973 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/256",
            "value": 0.4666089827087492,
            "unit": "us/iter",
            "extra": "iterations: 1497811\ncpu: 0.4665828999787021 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/512",
            "value": 0.8845141032942458,
            "unit": "us/iter",
            "extra": "iterations: 790170\ncpu: 0.8845018160649014 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1024",
            "value": 1.7419266626101164,
            "unit": "us/iter",
            "extra": "iterations: 400996\ncpu: 1.7418966772735687 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/2048",
            "value": 3.5092012715904275,
            "unit": "us/iter",
            "extra": "iterations: 199278\ncpu: 3.5091821475527265 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/4096",
            "value": 7.048850742673492,
            "unit": "us/iter",
            "extra": "iterations: 99640\ncpu: 7.048546768366077 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/8192",
            "value": 13.943747505923689,
            "unit": "us/iter",
            "extra": "iterations: 50219\ncpu: 13.942852306895784 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/16384",
            "value": 28.3489999187216,
            "unit": "us/iter",
            "extra": "iterations: 24607\ncpu: 28.349071402446317 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/32768",
            "value": 57.17537100317204,
            "unit": "us/iter",
            "extra": "iterations: 12291\ncpu: 57.17190627288252 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/65536",
            "value": 113.56002534523937,
            "unit": "us/iter",
            "extra": "iterations: 6155\ncpu: 113.55701056052064 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/131072",
            "value": 226.86844991897146,
            "unit": "us/iter",
            "extra": "iterations: 3085\ncpu: 226.8613290113452 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/262144",
            "value": 451.8328231865497,
            "unit": "us/iter",
            "extra": "iterations: 1544\ncpu: 451.8196243523307 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/524288",
            "value": 917.256287760404,
            "unit": "us/iter",
            "extra": "iterations: 768\ncpu: 917.194661458324 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1048576",
            "value": 4379.135648147815,
            "unit": "us/iter",
            "extra": "iterations: 162\ncpu: 4378.382098765405 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/256",
            "value": 0.522583316344659,
            "unit": "us/iter",
            "extra": "iterations: 1319507\ncpu: 0.522565321745169 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/512",
            "value": 0.9992434906230493,
            "unit": "us/iter",
            "extra": "iterations: 701296\ncpu: 0.9992191599552753 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1024",
            "value": 2.069649772854208,
            "unit": "us/iter",
            "extra": "iterations: 338329\ncpu: 2.069615374384111 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/2048",
            "value": 4.09169347364239,
            "unit": "us/iter",
            "extra": "iterations: 171336\ncpu: 4.091539431292862 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/4096",
            "value": 8.363870053618042,
            "unit": "us/iter",
            "extra": "iterations: 86351\ncpu: 8.343561742191744 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/8192",
            "value": 16.204728897830314,
            "unit": "us/iter",
            "extra": "iterations: 43242\ncpu: 16.2044262522546 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/16384",
            "value": 32.89275527009295,
            "unit": "us/iter",
            "extra": "iterations: 21252\ncpu: 32.89097967250116 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/32768",
            "value": 65.85456224221824,
            "unit": "us/iter",
            "extra": "iterations: 10668\ncpu: 65.85096550431193 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/65536",
            "value": 132.29799137608046,
            "unit": "us/iter",
            "extra": "iterations: 5334\ncpu: 132.29381327333996 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/131072",
            "value": 262.6059763868093,
            "unit": "us/iter",
            "extra": "iterations: 2668\ncpu: 262.58763118440396 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/262144",
            "value": 525.3939010654766,
            "unit": "us/iter",
            "extra": "iterations: 1314\ncpu: 525.3607305936104 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/524288",
            "value": 1109.327278662465,
            "unit": "us/iter",
            "extra": "iterations: 628\ncpu: 1109.2686305732436 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1048576",
            "value": 5132.191346774561,
            "unit": "us/iter",
            "extra": "iterations: 124\ncpu: 5131.672580645153 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}