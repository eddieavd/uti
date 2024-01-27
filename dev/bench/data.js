window.BENCHMARK_DATA = {
  "lastUpdate": 1706347159059,
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
          "id": "f28d92eacfa3195dc055dd15ebc1af60e91d98ea",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T09:49:35+01:00",
          "tree_id": "7a8467b9e2f9c150c208a5f6e888d5006d1cadce",
          "url": "https://github.com/eddieavd/uti/commit/f28d92eacfa3195dc055dd15ebc1af60e91d98ea"
        },
        "date": 1706347158159,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/256",
            "value": 0.30173734343195907,
            "unit": "us/iter",
            "extra": "iterations: 2303152\ncpu: 0.3017150843713311 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.5001424688994907,
            "unit": "us/iter",
            "extra": "iterations: 1401183\ncpu: 0.5001070523978666 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1024",
            "value": 0.8829787022766795,
            "unit": "us/iter",
            "extra": "iterations: 802621\ncpu: 0.882915846956409 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2048",
            "value": 2.913506826826652,
            "unit": "us/iter",
            "extra": "iterations: 236347\ncpu: 2.913335053967262 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 6.929639500916075,
            "unit": "us/iter",
            "extra": "iterations: 100985\ncpu: 6.929550923404473 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8192",
            "value": 15.011055592507342,
            "unit": "us/iter",
            "extra": "iterations: 46607\ncpu: 15.0105091509859 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16384",
            "value": 30.972853652058564,
            "unit": "us/iter",
            "extra": "iterations: 22590\ncpu: 30.97241699867196 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 124.60684673097892,
            "unit": "us/iter",
            "extra": "iterations: 5598\ncpu: 124.49885673454807 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/65536",
            "value": 294.2771176470589,
            "unit": "us/iter",
            "extra": "iterations: 2380\ncpu: 294.22184873949624 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/131072",
            "value": 633.6017902350817,
            "unit": "us/iter",
            "extra": "iterations: 1106\ncpu: 633.5768535262215 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/262144",
            "value": 1403.4947269076079,
            "unit": "us/iter",
            "extra": "iterations: 498\ncpu: 1403.424899598393 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/524288",
            "value": 2933.906756302488,
            "unit": "us/iter",
            "extra": "iterations: 238\ncpu: 2933.861764705881 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1048576",
            "value": 5243.818105263269,
            "unit": "us/iter",
            "extra": "iterations: 133\ncpu: 5243.432330827073 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2097152",
            "value": 9025.13779220763,
            "unit": "us/iter",
            "extra": "iterations: 77\ncpu: 9024.974025974017 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4194304",
            "value": 16131.30990697657,
            "unit": "us/iter",
            "extra": "iterations: 43\ncpu: 16129.490697674424 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8388608",
            "value": 21687.526812499415,
            "unit": "us/iter",
            "extra": "iterations: 32\ncpu: 21685.409374999963 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16777216",
            "value": 34036.247749999406,
            "unit": "us/iter",
            "extra": "iterations: 20\ncpu: 34034.48999999998 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/256",
            "value": 0.30611237882382486,
            "unit": "us/iter",
            "extra": "iterations: 2289951\ncpu: 0.3060962876498229 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.49860241283901663,
            "unit": "us/iter",
            "extra": "iterations: 1411698\ncpu: 0.49857844949840574 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1024",
            "value": 0.8907747725246865,
            "unit": "us/iter",
            "extra": "iterations: 788767\ncpu: 0.8907453024784244 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2048",
            "value": 1.6166744320235331,
            "unit": "us/iter",
            "extra": "iterations: 431532\ncpu: 1.6165758275168485 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.042051848476881,
            "unit": "us/iter",
            "extra": "iterations: 230460\ncpu: 3.0419348260001713 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8192",
            "value": 5.850756196282277,
            "unit": "us/iter",
            "extra": "iterations: 120072\ncpu: 5.850667932573782 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16384",
            "value": 11.47499568553071,
            "unit": "us/iter",
            "extra": "iterations: 59567\ncpu: 11.474724260076925 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 22.685689372325054,
            "unit": "us/iter",
            "extra": "iterations: 30844\ncpu: 22.68558876929063 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/65536",
            "value": 45.338335082266035,
            "unit": "us/iter",
            "extra": "iterations: 15438\ncpu: 45.33639720171 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/131072",
            "value": 93.13012485444455,
            "unit": "us/iter",
            "extra": "iterations: 7729\ncpu: 93.12786906456179 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/262144",
            "value": 180.19242165242062,
            "unit": "us/iter",
            "extra": "iterations: 3861\ncpu: 180.1800828800823 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/524288",
            "value": 360.2068722965952,
            "unit": "us/iter",
            "extra": "iterations: 1942\ncpu: 360.19073120494437 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1048576",
            "value": 721.6264059917211,
            "unit": "us/iter",
            "extra": "iterations: 968\ncpu: 721.5512396694195 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2097152",
            "value": 1440.5525082305048,
            "unit": "us/iter",
            "extra": "iterations: 486\ncpu: 1440.4390946502092 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4194304",
            "value": 2886.1764916664847,
            "unit": "us/iter",
            "extra": "iterations: 240\ncpu: 2885.80124999999 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8388608",
            "value": 8788.903063291371,
            "unit": "us/iter",
            "extra": "iterations: 79\ncpu: 8787.63544303797 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16777216",
            "value": 19845.00897142912,
            "unit": "us/iter",
            "extra": "iterations: 35\ncpu: 19840.459999999945 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/256",
            "value": 1.8877582234315944,
            "unit": "us/iter",
            "extra": "iterations: 371165\ncpu: 1.8877256745652318 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/512",
            "value": 3.6268881470675263,
            "unit": "us/iter",
            "extra": "iterations: 192619\ncpu: 3.6266775344072864 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1024",
            "value": 6.474898564097536,
            "unit": "us/iter",
            "extra": "iterations: 106205\ncpu: 6.474814745068458 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/2048",
            "value": 12.637839690657282,
            "unit": "us/iter",
            "extra": "iterations: 55343\ncpu: 12.637287461828903 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/4096",
            "value": 25.071395926137818,
            "unit": "us/iter",
            "extra": "iterations: 27836\ncpu: 25.069349044402962 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/8192",
            "value": 50.181187621026695,
            "unit": "us/iter",
            "extra": "iterations: 13943\ncpu: 50.177020727246884 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/16384",
            "value": 103.00570792746714,
            "unit": "us/iter",
            "extra": "iterations: 6673\ncpu: 102.99490484040204 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/32768",
            "value": 199.22764958723914,
            "unit": "us/iter",
            "extra": "iterations: 3513\ncpu: 199.21705095360065 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/65536",
            "value": 388.12578359906905,
            "unit": "us/iter",
            "extra": "iterations: 1756\ncpu: 388.0780182232322 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/131072",
            "value": 762.7376337868174,
            "unit": "us/iter",
            "extra": "iterations: 882\ncpu: 762.6846938775507 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/262144",
            "value": 1550.0447022727246,
            "unit": "us/iter",
            "extra": "iterations: 440\ncpu: 1549.9679545454565 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/524288",
            "value": 8975.94196,
            "unit": "us/iter",
            "extra": "iterations: 75\ncpu: 8974.750666666676 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1048576",
            "value": 15605.436666666921,
            "unit": "us/iter",
            "extra": "iterations: 45\ncpu: 15603.866666666654 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/256",
            "value": 1.1264198237849563,
            "unit": "us/iter",
            "extra": "iterations: 617995\ncpu: 1.1262799860840291 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/512",
            "value": 2.1775990403016077,
            "unit": "us/iter",
            "extra": "iterations: 320309\ncpu: 2.1774433437711758 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1024",
            "value": 4.120028774646887,
            "unit": "us/iter",
            "extra": "iterations: 169698\ncpu: 4.119626041556157 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/2048",
            "value": 7.968929766148839,
            "unit": "us/iter",
            "extra": "iterations: 89202\ncpu: 7.968482769444665 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/4096",
            "value": 16.106483292789058,
            "unit": "us/iter",
            "extra": "iterations: 43574\ncpu: 16.105464267682578 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/8192",
            "value": 31.485411632303883,
            "unit": "us/iter",
            "extra": "iterations: 22214\ncpu: 31.48354191050693 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/16384",
            "value": 63.79651849483971,
            "unit": "us/iter",
            "extra": "iterations: 10949\ncpu: 63.7932596584163 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/32768",
            "value": 124.82085323560923,
            "unit": "us/iter",
            "extra": "iterations: 5594\ncpu: 124.81435466571314 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/65536",
            "value": 249.66821725126863,
            "unit": "us/iter",
            "extra": "iterations: 2794\ncpu: 249.66424481030916 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/131072",
            "value": 491.22278807018165,
            "unit": "us/iter",
            "extra": "iterations: 1425\ncpu: 491.20315789473693 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/262144",
            "value": 1003.1290143471616,
            "unit": "us/iter",
            "extra": "iterations: 697\ncpu: 1003.1035868005753 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/524288",
            "value": 8101.314639534763,
            "unit": "us/iter",
            "extra": "iterations: 86\ncpu: 8100.162790697636 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1048576",
            "value": 13625.75069230751,
            "unit": "us/iter",
            "extra": "iterations: 52\ncpu: 13624.43461538472 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/256",
            "value": 0.1695625013350019,
            "unit": "us/iter",
            "extra": "iterations: 4119848\ncpu: 0.16954572110427318 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/512",
            "value": 0.3360934834050974,
            "unit": "us/iter",
            "extra": "iterations: 2083803\ncpu: 0.3360661732419034 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/1024",
            "value": 0.6533058520925511,
            "unit": "us/iter",
            "extra": "iterations: 1070318\ncpu: 0.653258657707333 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/2048",
            "value": 1.2864741113637923,
            "unit": "us/iter",
            "extra": "iterations: 544486\ncpu: 1.2863972627395361 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/4096",
            "value": 2.5529549658635027,
            "unit": "us/iter",
            "extra": "iterations: 274192\ncpu: 2.5527798039330136 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/8192",
            "value": 5.113354046887107,
            "unit": "us/iter",
            "extra": "iterations: 136883\ncpu: 5.113032297655656 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/16384",
            "value": 10.319902448371451,
            "unit": "us/iter",
            "extra": "iterations: 67841\ncpu: 10.319305434766568 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/32768",
            "value": 20.636426888181198,
            "unit": "us/iter",
            "extra": "iterations: 33948\ncpu: 20.63447331212448 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/65536",
            "value": 41.53170549163864,
            "unit": "us/iter",
            "extra": "iterations: 16862\ncpu: 41.52990748428439 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/131072",
            "value": 82.93129415945798,
            "unit": "us/iter",
            "extra": "iterations: 8441\ncpu: 82.9229593650038 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/262144",
            "value": 165.66231116894642,
            "unit": "us/iter",
            "extra": "iterations: 4226\ncpu: 165.65052058684284 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/524288",
            "value": 331.2045692671447,
            "unit": "us/iter",
            "extra": "iterations: 2115\ncpu: 331.1696926713967 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/1048576",
            "value": 662.5342762535881,
            "unit": "us/iter",
            "extra": "iterations: 1057\ncpu: 662.4984862819333 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/2097152",
            "value": 1326.7754555765405,
            "unit": "us/iter",
            "extra": "iterations: 529\ncpu: 1326.6790170132394 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/4194304",
            "value": 2651.47378787866,
            "unit": "us/iter",
            "extra": "iterations: 264\ncpu: 2651.301893939416 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/8388608",
            "value": 7276.527421052641,
            "unit": "us/iter",
            "extra": "iterations: 95\ncpu: 7275.878947368441 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/16777216",
            "value": 15671.700266667207,
            "unit": "us/iter",
            "extra": "iterations: 45\ncpu: 15667.522222222235 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/256",
            "value": 0.19812229378421478,
            "unit": "us/iter",
            "extra": "iterations: 3509467\ncpu: 0.198113930121011 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/512",
            "value": 0.38796967329216786,
            "unit": "us/iter",
            "extra": "iterations: 1798151\ncpu: 0.38795329202052903 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/1024",
            "value": 0.7394791149676128,
            "unit": "us/iter",
            "extra": "iterations: 955852\ncpu: 0.7394028573461081 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/2048",
            "value": 1.4348385284127931,
            "unit": "us/iter",
            "extra": "iterations: 481385\ncpu: 1.4346961371874642 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/4096",
            "value": 2.8418899644393147,
            "unit": "us/iter",
            "extra": "iterations: 246902\ncpu: 2.8416995407084564 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/8192",
            "value": 5.62830291923982,
            "unit": "us/iter",
            "extra": "iterations: 124690\ncpu: 5.628014275402958 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/16384",
            "value": 11.213626279480193,
            "unit": "us/iter",
            "extra": "iterations: 62330\ncpu: 11.213296967752292 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/32768",
            "value": 22.41843496221365,
            "unit": "us/iter",
            "extra": "iterations: 31228\ncpu: 22.41765402843593 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/65536",
            "value": 45.1010599858392,
            "unit": "us/iter",
            "extra": "iterations: 15537\ncpu: 45.098603333977294 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/131072",
            "value": 90.0649201290332,
            "unit": "us/iter",
            "extra": "iterations: 7750\ncpu: 90.06343225806383 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/262144",
            "value": 180.61335206184467,
            "unit": "us/iter",
            "extra": "iterations: 3880\ncpu: 180.60427835051368 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/524288",
            "value": 359.8994634773658,
            "unit": "us/iter",
            "extra": "iterations: 1944\ncpu: 359.894701646089 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/1048576",
            "value": 721.8797332636051,
            "unit": "us/iter",
            "extra": "iterations: 956\ncpu: 721.8498953974912 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/2097152",
            "value": 1440.8930925925495,
            "unit": "us/iter",
            "extra": "iterations: 486\ncpu: 1440.79238683127 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/4194304",
            "value": 2920.28001666651,
            "unit": "us/iter",
            "extra": "iterations: 240\ncpu: 2919.910833333302 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/8388608",
            "value": 7935.750397590359,
            "unit": "us/iter",
            "extra": "iterations: 83\ncpu: 7895.959036144562 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/16777216",
            "value": 16664.09900000027,
            "unit": "us/iter",
            "extra": "iterations: 42\ncpu: 16660.509523809706 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/256",
            "value": 0.46164758277681267,
            "unit": "us/iter",
            "extra": "iterations: 1518209\ncpu: 0.46162267513892286 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/512",
            "value": 0.8774177408459348,
            "unit": "us/iter",
            "extra": "iterations: 796422\ncpu: 0.8773419117000867 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1024",
            "value": 1.730067246353841,
            "unit": "us/iter",
            "extra": "iterations: 404126\ncpu: 1.730020835086096 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/2048",
            "value": 3.500058608296797,
            "unit": "us/iter",
            "extra": "iterations: 200057\ncpu: 3.5000119965809553 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/4096",
            "value": 6.964294449193885,
            "unit": "us/iter",
            "extra": "iterations: 100598\ncpu: 6.9641503807233915 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/8192",
            "value": 14.013848332234398,
            "unit": "us/iter",
            "extra": "iterations: 50037\ncpu: 14.013386094290217 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/16384",
            "value": 28.223865989357314,
            "unit": "us/iter",
            "extra": "iterations: 24804\ncpu: 28.22209321077206 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/32768",
            "value": 56.76902201537741,
            "unit": "us/iter",
            "extra": "iterations: 12355\ncpu: 56.76813435855991 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/65536",
            "value": 113.37518084934615,
            "unit": "us/iter",
            "extra": "iterations: 6193\ncpu: 113.37159696431243 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/131072",
            "value": 226.74398866580827,
            "unit": "us/iter",
            "extra": "iterations: 3088\ncpu: 226.7429404145079 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/262144",
            "value": 453.3119393156831,
            "unit": "us/iter",
            "extra": "iterations: 1549\ncpu: 453.29335054873536 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/524288",
            "value": 906.1718204134136,
            "unit": "us/iter",
            "extra": "iterations: 774\ncpu: 906.1484496123879 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1048576",
            "value": 4244.018759036285,
            "unit": "us/iter",
            "extra": "iterations: 166\ncpu: 4243.396385542134 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/256",
            "value": 0.5459220063860932,
            "unit": "us/iter",
            "extra": "iterations: 1281528\ncpu: 0.5458899844560645 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/512",
            "value": 1.0212588520307648,
            "unit": "us/iter",
            "extra": "iterations: 685210\ncpu: 1.0212035726273694 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1024",
            "value": 2.082428519131402,
            "unit": "us/iter",
            "extra": "iterations: 335992\ncpu: 2.0823174361294234 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/2048",
            "value": 4.10044200441549,
            "unit": "us/iter",
            "extra": "iterations: 170763\ncpu: 4.100332039141997 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/4096",
            "value": 8.174980830410394,
            "unit": "us/iter",
            "extra": "iterations: 85813\ncpu: 8.174869774975738 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/8192",
            "value": 16.30740492154344,
            "unit": "us/iter",
            "extra": "iterations: 42954\ncpu: 16.307340410672047 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/16384",
            "value": 32.95163207859096,
            "unit": "us/iter",
            "extra": "iterations: 21173\ncpu: 32.951225617531655 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/32768",
            "value": 65.70027050495622,
            "unit": "us/iter",
            "extra": "iterations: 10595\ncpu: 65.69892402076482 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/65536",
            "value": 131.87767847719866,
            "unit": "us/iter",
            "extra": "iterations: 5306\ncpu: 131.87427440633107 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/131072",
            "value": 263.4241889348979,
            "unit": "us/iter",
            "extra": "iterations: 2657\ncpu: 263.42314640572096 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/262144",
            "value": 526.9492956259651,
            "unit": "us/iter",
            "extra": "iterations: 1326\ncpu: 526.8887631975894 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/524288",
            "value": 1054.7893036253847,
            "unit": "us/iter",
            "extra": "iterations: 662\ncpu: 1054.7238670694942 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1048576",
            "value": 4523.628013071903,
            "unit": "us/iter",
            "extra": "iterations: 153\ncpu: 4522.960130718919 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}