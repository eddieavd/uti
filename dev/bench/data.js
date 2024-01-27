window.BENCHMARK_DATA = {
  "lastUpdate": 1706348678533,
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
          "id": "efd338732f9d5acd01228918beab7f0187464a2c",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T10:29:52+01:00",
          "tree_id": "6fa096d28f110842edd419c969d330ed0149d328",
          "url": "https://github.com/eddieavd/uti/commit/efd338732f9d5acd01228918beab7f0187464a2c"
        },
        "date": 1706347971883,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/256",
            "value": 0.30811826901084494,
            "unit": "us/iter",
            "extra": "iterations: 2278027\ncpu: 0.3081094297828779 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.5064888688438486,
            "unit": "us/iter",
            "extra": "iterations: 1376901\ncpu: 0.5064664779820771 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1024",
            "value": 0.8761377409028199,
            "unit": "us/iter",
            "extra": "iterations: 803073\ncpu: 0.8761125078293011 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2048",
            "value": 2.9160819515266305,
            "unit": "us/iter",
            "extra": "iterations: 241411\ncpu: 2.916021225213433 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 6.9354201182262,
            "unit": "us/iter",
            "extra": "iterations: 100993\ncpu: 6.93509253116553 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8192",
            "value": 15.030258382514386,
            "unit": "us/iter",
            "extra": "iterations: 46257\ncpu: 15.029426897550639 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16384",
            "value": 31.38218168773977,
            "unit": "us/iter",
            "extra": "iterations: 22302\ncpu: 31.38008250381134 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 127.69041905106954,
            "unit": "us/iter",
            "extra": "iterations: 5522\ncpu: 126.90315103223475 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/65536",
            "value": 309.02459168081333,
            "unit": "us/iter",
            "extra": "iterations: 2356\ncpu: 307.9591256366725 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/256",
            "value": 0.30684749159462277,
            "unit": "us/iter",
            "extra": "iterations: 2286333\ncpu: 0.30681864802721226 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.5001733020000074,
            "unit": "us/iter",
            "extra": "iterations: 1000000\ncpu: 0.5001406999999993 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1024",
            "value": 0.8686447215520012,
            "unit": "us/iter",
            "extra": "iterations: 812360\ncpu: 0.8686307794573842 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2048",
            "value": 1.582049687913816,
            "unit": "us/iter",
            "extra": "iterations: 443307\ncpu: 1.5819039627165807 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.099294777890202,
            "unit": "us/iter",
            "extra": "iterations: 233871\ncpu: 3.099066579439087 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8192",
            "value": 5.8591509444955445,
            "unit": "us/iter",
            "extra": "iterations: 120170\ncpu: 5.858897395356585 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16384",
            "value": 11.435684943401125,
            "unit": "us/iter",
            "extra": "iterations: 61043\ncpu: 11.4352980685746 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 22.66740860807041,
            "unit": "us/iter",
            "extra": "iterations: 30878\ncpu: 22.66694086404561 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/65536",
            "value": 45.15111914756217,
            "unit": "us/iter",
            "extra": "iterations: 15485\ncpu: 45.14898934452696 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/256",
            "value": 1.8236800940316147,
            "unit": "us/iter",
            "extra": "iterations: 382850\ncpu: 1.8233490923338096 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/512",
            "value": 3.645920401522103,
            "unit": "us/iter",
            "extra": "iterations: 199740\ncpu: 3.6457900270351375 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1024",
            "value": 7.1024293636954585,
            "unit": "us/iter",
            "extra": "iterations: 98632\ncpu: 7.102302498175052 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/2048",
            "value": 14.021977233797143,
            "unit": "us/iter",
            "extra": "iterations: 50206\ncpu: 14.021258415328845 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/4096",
            "value": 27.719358972335968,
            "unit": "us/iter",
            "extra": "iterations: 25339\ncpu: 27.71823671020951 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/8192",
            "value": 213.4084001236903,
            "unit": "us/iter",
            "extra": "iterations: 3234\ncpu: 212.60417439703218 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/16384",
            "value": 460.93302785145505,
            "unit": "us/iter",
            "extra": "iterations: 1508\ncpu: 460.0142572944294 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/32768",
            "value": 973.7180817175173,
            "unit": "us/iter",
            "extra": "iterations: 722\ncpu: 972.5170360110799 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/65536",
            "value": 1994.209840909084,
            "unit": "us/iter",
            "extra": "iterations: 352\ncpu: 1991.6252840909044 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/256",
            "value": 1.0859668663290651,
            "unit": "us/iter",
            "extra": "iterations: 641583\ncpu: 1.0859019020142393 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/512",
            "value": 2.0862242398573505,
            "unit": "us/iter",
            "extra": "iterations: 335266\ncpu: 2.086104168033746 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1024",
            "value": 4.150072008377485,
            "unit": "us/iter",
            "extra": "iterations: 169022\ncpu: 4.149776360473793 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/2048",
            "value": 8.039452055269141,
            "unit": "us/iter",
            "extra": "iterations: 86631\ncpu: 8.038755180016429 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/4096",
            "value": 15.645324073456104,
            "unit": "us/iter",
            "extra": "iterations: 44925\ncpu: 15.64382192543125 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/8192",
            "value": 31.333746403040692,
            "unit": "us/iter",
            "extra": "iterations: 22102\ncpu: 31.329612704732718 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/16384",
            "value": 64.83863959955794,
            "unit": "us/iter",
            "extra": "iterations: 10788\ncpu: 64.83682795698944 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/32768",
            "value": 127.29469166362955,
            "unit": "us/iter",
            "extra": "iterations: 5494\ncpu: 127.28638514743339 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/65536",
            "value": 1843.3585171504278,
            "unit": "us/iter",
            "extra": "iterations: 379\ncpu: 1840.6002638522543 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/256",
            "value": 0.16994984238005748,
            "unit": "us/iter",
            "extra": "iterations: 4110203\ncpu: 0.16994892952975776 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/512",
            "value": 0.3361043060989967,
            "unit": "us/iter",
            "extra": "iterations: 2078517\ncpu: 0.3360950138969297 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/1024",
            "value": 0.6530350456336727,
            "unit": "us/iter",
            "extra": "iterations: 1073001\ncpu: 0.6530316374355701 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/2048",
            "value": 1.2860588627849747,
            "unit": "us/iter",
            "extra": "iterations: 542448\ncpu: 1.286011931097547 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/4096",
            "value": 2.5544641233682883,
            "unit": "us/iter",
            "extra": "iterations: 274106\ncpu: 2.554390637198754 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/8192",
            "value": 5.107892306233029,
            "unit": "us/iter",
            "extra": "iterations: 137046\ncpu: 5.107862323599392 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/16384",
            "value": 10.338689092250407,
            "unit": "us/iter",
            "extra": "iterations: 67750\ncpu: 10.338087084870864 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/32768",
            "value": 20.681349158049443,
            "unit": "us/iter",
            "extra": "iterations: 33850\ncpu: 20.68017134416555 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/65536",
            "value": 41.401986988406655,
            "unit": "us/iter",
            "extra": "iterations: 16908\ncpu: 41.399792997397334 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/256",
            "value": 0.20016949251619637,
            "unit": "us/iter",
            "extra": "iterations: 3506910\ncpu: 0.2001638479459112 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/512",
            "value": 0.38711254906976095,
            "unit": "us/iter",
            "extra": "iterations: 1821641\ncpu: 0.38709948886745454 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/1024",
            "value": 0.7336577663376549,
            "unit": "us/iter",
            "extra": "iterations: 948317\ncpu: 0.7336366425994711 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/2048",
            "value": 1.4353420477392271,
            "unit": "us/iter",
            "extra": "iterations: 490414\ncpu: 1.4352824348407671 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/4096",
            "value": 2.8468203683605524,
            "unit": "us/iter",
            "extra": "iterations: 246009\ncpu: 2.8468039787162143 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/8192",
            "value": 5.738496855900842,
            "unit": "us/iter",
            "extra": "iterations: 124678\ncpu: 5.738465487094795 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/16384",
            "value": 11.277212609051956,
            "unit": "us/iter",
            "extra": "iterations: 62241\ncpu: 11.27699426423099 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/32768",
            "value": 22.494815099312493,
            "unit": "us/iter",
            "extra": "iterations: 31114\ncpu: 22.494028411647427 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/65536",
            "value": 44.86843197845857,
            "unit": "us/iter",
            "extra": "iterations: 15598\ncpu: 44.866008462623576 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/256",
            "value": 0.44628116369893206,
            "unit": "us/iter",
            "extra": "iterations: 1558135\ncpu: 0.44625138386596874 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/512",
            "value": 0.8506552713037162,
            "unit": "us/iter",
            "extra": "iterations: 826067\ncpu: 0.8506259177524362 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1024",
            "value": 1.666744946170656,
            "unit": "us/iter",
            "extra": "iterations: 417802\ncpu: 1.6666995371013065 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/2048",
            "value": 3.367156865859901,
            "unit": "us/iter",
            "extra": "iterations: 207738\ncpu: 3.367135045104902 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/4096",
            "value": 6.784959213316412,
            "unit": "us/iter",
            "extra": "iterations: 103269\ncpu: 6.78492577637048 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/8192",
            "value": 13.729372782107868,
            "unit": "us/iter",
            "extra": "iterations: 51062\ncpu: 13.728882534957485 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/16384",
            "value": 27.96861487081191,
            "unit": "us/iter",
            "extra": "iterations: 25002\ncpu: 27.967674586033198 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/32768",
            "value": 55.31305397277426,
            "unit": "us/iter",
            "extra": "iterations: 12636\ncpu: 55.31008230452636 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/65536",
            "value": 110.37876981250655,
            "unit": "us/iter",
            "extra": "iterations: 6347\ncpu: 110.37803686781142 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/256",
            "value": 0.5115152919559601,
            "unit": "us/iter",
            "extra": "iterations: 1368203\ncpu: 0.5115072105528181 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/512",
            "value": 0.9867734340474541,
            "unit": "us/iter",
            "extra": "iterations: 710526\ncpu: 0.9867263126191002 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1024",
            "value": 2.0487837032488945,
            "unit": "us/iter",
            "extra": "iterations: 341970\ncpu: 2.0486949147585913 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/2048",
            "value": 4.072178666356432,
            "unit": "us/iter",
            "extra": "iterations: 171935\ncpu: 4.071944048623019 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/4096",
            "value": 8.170552773789822,
            "unit": "us/iter",
            "extra": "iterations: 85677\ncpu: 8.170412129276267 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/8192",
            "value": 16.44107489617281,
            "unit": "us/iter",
            "extra": "iterations: 42619\ncpu: 16.440779933832424 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/16384",
            "value": 32.95985337463597,
            "unit": "us/iter",
            "extra": "iterations: 21306\ncpu: 32.95855158171413 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/32768",
            "value": 66.03640239043449,
            "unit": "us/iter",
            "extra": "iterations: 10542\ncpu: 66.0330772149492 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/65536",
            "value": 132.48942296812524,
            "unit": "us/iter",
            "extra": "iterations: 5303\ncpu: 132.48289647369347 us\nthreads: 1"
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
          "id": "efd338732f9d5acd01228918beab7f0187464a2c",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T10:29:52+01:00",
          "tree_id": "6fa096d28f110842edd419c969d330ed0149d328",
          "url": "https://github.com/eddieavd/uti/commit/efd338732f9d5acd01228918beab7f0187464a2c"
        },
        "date": 1706348678179,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/256",
            "value": 0.30109750969172727,
            "unit": "us/iter",
            "extra": "iterations: 2233860\ncpu: 0.3010952342581898 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.5002405796747637,
            "unit": "us/iter",
            "extra": "iterations: 1392229\ncpu: 0.5002125368743217 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1024",
            "value": 0.8681232031146223,
            "unit": "us/iter",
            "extra": "iterations: 805491\ncpu: 0.868073510442699 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2048",
            "value": 2.893175335647433,
            "unit": "us/iter",
            "extra": "iterations: 239090\ncpu: 2.8930189468401015 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 6.919765148819852,
            "unit": "us/iter",
            "extra": "iterations: 101196\ncpu: 6.919397011739593 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8192",
            "value": 14.988056866355677,
            "unit": "us/iter",
            "extra": "iterations: 46706\ncpu: 14.987751038410478 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16384",
            "value": 30.969358713446606,
            "unit": "us/iter",
            "extra": "iterations: 22603\ncpu: 30.96807945847897 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 125.34578854073114,
            "unit": "us/iter",
            "extra": "iterations: 5585\ncpu: 125.23713518352727 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/65536",
            "value": 297.0420692732664,
            "unit": "us/iter",
            "extra": "iterations: 2353\ncpu: 296.9903102422439 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/256",
            "value": 0.3070525596836609,
            "unit": "us/iter",
            "extra": "iterations: 2191052\ncpu: 0.3070501749844369 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.49896636114957527,
            "unit": "us/iter",
            "extra": "iterations: 1397194\ncpu: 0.4989631361142406 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1024",
            "value": 0.8699011232891131,
            "unit": "us/iter",
            "extra": "iterations: 792138\ncpu: 0.8698712850538675 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2048",
            "value": 1.5842405433827795,
            "unit": "us/iter",
            "extra": "iterations: 439322\ncpu: 1.5842523251737923 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.004647737516573,
            "unit": "us/iter",
            "extra": "iterations: 231847\ncpu: 3.004421450353035 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8192",
            "value": 5.807817213481639,
            "unit": "us/iter",
            "extra": "iterations: 120638\ncpu: 5.8077123294484245 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16384",
            "value": 11.400226683087405,
            "unit": "us/iter",
            "extra": "iterations: 60900\ncpu: 11.399980295566504 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 22.60935771480793,
            "unit": "us/iter",
            "extra": "iterations: 30597\ncpu: 22.608598882243374 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/65536",
            "value": 45.074708693408475,
            "unit": "us/iter",
            "extra": "iterations: 15506\ncpu: 45.07444215142513 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/256",
            "value": 1.897573260269802,
            "unit": "us/iter",
            "extra": "iterations: 372644\ncpu: 1.8975630897049207 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/512",
            "value": 3.4778795862501686,
            "unit": "us/iter",
            "extra": "iterations: 201281\ncpu: 3.477826521132147 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1024",
            "value": 6.764824727630862,
            "unit": "us/iter",
            "extra": "iterations: 103536\ncpu: 6.764657703600685 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/2048",
            "value": 13.298721623782107,
            "unit": "us/iter",
            "extra": "iterations: 52544\ncpu: 13.298551690012184 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/4096",
            "value": 27.465436725594824,
            "unit": "us/iter",
            "extra": "iterations: 26472\ncpu: 27.464358567543087 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/8192",
            "value": 211.79212080942534,
            "unit": "us/iter",
            "extra": "iterations: 3311\ncpu: 211.67553609181525 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/16384",
            "value": 464.0124001326985,
            "unit": "us/iter",
            "extra": "iterations: 1507\ncpu: 463.76091572660926 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/32768",
            "value": 952.6390680271631,
            "unit": "us/iter",
            "extra": "iterations: 735\ncpu: 952.5268027210905 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/65536",
            "value": 1943.5549666667382,
            "unit": "us/iter",
            "extra": "iterations: 360\ncpu: 1943.3744444444517 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/256",
            "value": 1.1152297305395946,
            "unit": "us/iter",
            "extra": "iterations: 634082\ncpu: 1.11522626411095 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/512",
            "value": 2.1148641947638738,
            "unit": "us/iter",
            "extra": "iterations: 330164\ncpu: 2.114767509480138 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1024",
            "value": 4.169781741531466,
            "unit": "us/iter",
            "extra": "iterations: 168415\ncpu: 4.169646409167837 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/2048",
            "value": 8.13062248199574,
            "unit": "us/iter",
            "extra": "iterations: 86229\ncpu: 8.130248524278375 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/4096",
            "value": 15.72073548591595,
            "unit": "us/iter",
            "extra": "iterations: 44164\ncpu: 15.71992346707722 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/8192",
            "value": 31.349098068149676,
            "unit": "us/iter",
            "extra": "iterations: 22362\ncpu: 31.347643323495216 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/16384",
            "value": 61.745914318321724,
            "unit": "us/iter",
            "extra": "iterations: 11391\ncpu: 61.74278816609586 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/32768",
            "value": 127.01261591445106,
            "unit": "us/iter",
            "extra": "iterations: 5517\ncpu: 127.01314119992747 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/65536",
            "value": 1833.1609475065072,
            "unit": "us/iter",
            "extra": "iterations: 381\ncpu: 1833.0889763779578 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/256",
            "value": 0.16997039932613078,
            "unit": "us/iter",
            "extra": "iterations: 4102812\ncpu: 0.16996508735959634 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/512",
            "value": 0.33645987713254677,
            "unit": "us/iter",
            "extra": "iterations: 2079151\ncpu: 0.3364481944793806 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/1024",
            "value": 0.6530350450655223,
            "unit": "us/iter",
            "extra": "iterations: 1073104\ncpu: 0.6530125691452058 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/2048",
            "value": 1.2865976754187607,
            "unit": "us/iter",
            "extra": "iterations: 544098\ncpu: 1.2865237512359928 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/4096",
            "value": 2.55161106108708,
            "unit": "us/iter",
            "extra": "iterations: 274313\ncpu: 2.5515312799612087 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/8192",
            "value": 5.1060444029796255,
            "unit": "us/iter",
            "extra": "iterations: 137198\ncpu: 5.1058317176635235 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/16384",
            "value": 10.326898642867462,
            "unit": "us/iter",
            "extra": "iterations: 67790\ncpu: 10.326813689334644 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/32768",
            "value": 20.647507758570303,
            "unit": "us/iter",
            "extra": "iterations: 33898\ncpu: 20.647380376423385 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/65536",
            "value": 41.37197231424538,
            "unit": "us/iter",
            "extra": "iterations: 16904\ncpu: 41.371775911027356 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/256",
            "value": 0.19803766781473592,
            "unit": "us/iter",
            "extra": "iterations: 3520698\ncpu: 0.19803851395376895 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/512",
            "value": 0.38402385740929695,
            "unit": "us/iter",
            "extra": "iterations: 1820315\ncpu: 0.3840027687515645 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/1024",
            "value": 0.7340079746482085,
            "unit": "us/iter",
            "extra": "iterations: 957409\ncpu: 0.7340029182930212 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/2048",
            "value": 1.4355124742958436,
            "unit": "us/iter",
            "extra": "iterations: 487763\ncpu: 1.4353989540002097 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/4096",
            "value": 2.828963156780203,
            "unit": "us/iter",
            "extra": "iterations: 245554\ncpu: 2.82886697019801 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/8192",
            "value": 5.634539328998759,
            "unit": "us/iter",
            "extra": "iterations: 124590\ncpu: 5.6342170318645515 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/16384",
            "value": 11.256026612488238,
            "unit": "us/iter",
            "extra": "iterations: 62264\ncpu: 11.255645316715976 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/32768",
            "value": 22.45219245898438,
            "unit": "us/iter",
            "extra": "iterations: 31269\ncpu: 22.45085228181256 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/65536",
            "value": 44.88577568537172,
            "unit": "us/iter",
            "extra": "iterations: 15612\ncpu: 44.883660005124106 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/256",
            "value": 0.45125137721824765,
            "unit": "us/iter",
            "extra": "iterations: 1554946\ncpu: 0.45122306498103515 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/512",
            "value": 0.8525637929906331,
            "unit": "us/iter",
            "extra": "iterations: 825122\ncpu: 0.8525373217536322 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1024",
            "value": 1.6776689573215753,
            "unit": "us/iter",
            "extra": "iterations: 418221\ncpu: 1.677559472145117 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/2048",
            "value": 3.3730421121894123,
            "unit": "us/iter",
            "extra": "iterations: 206686\ncpu: 3.3728249615358794 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/4096",
            "value": 6.787814229172187,
            "unit": "us/iter",
            "extra": "iterations: 103337\ncpu: 6.787468186612688 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/8192",
            "value": 13.875083303743518,
            "unit": "us/iter",
            "extra": "iterations: 50694\ncpu: 13.874077800134035 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/16384",
            "value": 28.173543035494497,
            "unit": "us/iter",
            "extra": "iterations: 24991\ncpu: 28.1718418630707 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/32768",
            "value": 55.84577572263415,
            "unit": "us/iter",
            "extra": "iterations: 12489\ncpu: 55.843654415885915 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/65536",
            "value": 111.61920587296159,
            "unit": "us/iter",
            "extra": "iterations: 6266\ncpu: 111.6142515161191 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/256",
            "value": 0.5490693808390636,
            "unit": "us/iter",
            "extra": "iterations: 1276534\ncpu: 0.5490354350138722 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/512",
            "value": 1.0204550847618126,
            "unit": "us/iter",
            "extra": "iterations: 686571\ncpu: 1.020447848802241 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1024",
            "value": 2.1146378155977863,
            "unit": "us/iter",
            "extra": "iterations: 331276\ncpu: 2.1146424733455005 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/2048",
            "value": 4.13695717247513,
            "unit": "us/iter",
            "extra": "iterations: 167369\ncpu: 4.136176352849107 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/4096",
            "value": 8.184320323344625,
            "unit": "us/iter",
            "extra": "iterations: 85729\ncpu: 8.183963419612951 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/8192",
            "value": 16.503407833883834,
            "unit": "us/iter",
            "extra": "iterations: 42380\ncpu: 16.503319962246376 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/16384",
            "value": 33.117469397405856,
            "unit": "us/iter",
            "extra": "iterations: 21142\ncpu: 33.11600132437774 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/32768",
            "value": 66.54594107551591,
            "unit": "us/iter",
            "extra": "iterations: 10488\ncpu: 66.54217200610236 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/65536",
            "value": 132.26401587002175,
            "unit": "us/iter",
            "extra": "iterations: 5293\ncpu: 132.26077838654825 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}