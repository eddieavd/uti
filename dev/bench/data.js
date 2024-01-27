window.BENCHMARK_DATA = {
  "lastUpdate": 1706349331972,
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
          "id": "e6f8370b4dcb5c4e3105be96a6ad585291617aee",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T10:52:16+01:00",
          "tree_id": "1aeaaf7c61845e7d31f1701da5f3b6a0d8ec238c",
          "url": "https://github.com/eddieavd/uti/commit/e6f8370b4dcb5c4e3105be96a6ad585291617aee"
        },
        "date": 1706349330999,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/1024",
            "value": 0.8704491439767127,
            "unit": "us/iter",
            "extra": "iterations: 803366\ncpu: 0.8704090041151854 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2048",
            "value": 2.893948015773064,
            "unit": "us/iter",
            "extra": "iterations: 238380\ncpu: 2.8937931034482753 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 7.167005983865918,
            "unit": "us/iter",
            "extra": "iterations: 97930\ncpu: 7.166707852547738 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/8192",
            "value": 15.26735941581097,
            "unit": "us/iter",
            "extra": "iterations: 45944\ncpu: 15.267007661500958 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16384",
            "value": 31.61717505529715,
            "unit": "us/iter",
            "extra": "iterations: 22153\ncpu: 31.615894009840645 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 125.8506811516478,
            "unit": "us/iter",
            "extra": "iterations: 5592\ncpu: 125.69814020028616 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/65536",
            "value": 295.439907594929,
            "unit": "us/iter",
            "extra": "iterations: 2370\ncpu: 295.358818565401 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/131072",
            "value": 635.4505865209459,
            "unit": "us/iter",
            "extra": "iterations: 1098\ncpu: 635.3685792349727 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/262144",
            "value": 1404.927204819283,
            "unit": "us/iter",
            "extra": "iterations: 498\ncpu: 1404.8411646586358 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1024",
            "value": 0.8634057961744365,
            "unit": "us/iter",
            "extra": "iterations: 812950\ncpu: 0.8633812657605012 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2048",
            "value": 1.5849294438402692,
            "unit": "us/iter",
            "extra": "iterations: 444171\ncpu: 1.584873618493777 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 2.992114734428475,
            "unit": "us/iter",
            "extra": "iterations: 234193\ncpu: 2.9920582596405554 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/8192",
            "value": 5.800515904226058,
            "unit": "us/iter",
            "extra": "iterations: 120534\ncpu: 5.80030862661158 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16384",
            "value": 11.391918629237118,
            "unit": "us/iter",
            "extra": "iterations: 61484\ncpu: 11.391805998308499 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 22.588541790179093,
            "unit": "us/iter",
            "extra": "iterations: 31036\ncpu: 22.588320015465936 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/65536",
            "value": 45.54308949240315,
            "unit": "us/iter",
            "extra": "iterations: 15465\ncpu: 45.542004526349785 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/131072",
            "value": 90.27224648885593,
            "unit": "us/iter",
            "extra": "iterations: 7761\ncpu: 90.27044195335648 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/262144",
            "value": 180.32535394126467,
            "unit": "us/iter",
            "extra": "iterations: 3882\ncpu: 180.32081401339474 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1024",
            "value": 6.792001544919185,
            "unit": "us/iter",
            "extra": "iterations: 102918\ncpu: 6.7919149225597195 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/2048",
            "value": 13.281023684908828,
            "unit": "us/iter",
            "extra": "iterations: 52734\ncpu: 13.280557135813773 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/4096",
            "value": 26.244879383415014,
            "unit": "us/iter",
            "extra": "iterations: 26663\ncpu: 26.244196076960606 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/8192",
            "value": 52.69806030339258,
            "unit": "us/iter",
            "extra": "iterations: 13316\ncpu: 52.696372784620216 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/16384",
            "value": 103.59037699299655,
            "unit": "us/iter",
            "extra": "iterations: 6711\ncpu: 103.58730442556983 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/32768",
            "value": 951.4573827160617,
            "unit": "us/iter",
            "extra": "iterations: 729\ncpu: 951.3783264746243 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/65536",
            "value": 1937.3374888888388,
            "unit": "us/iter",
            "extra": "iterations: 360\ncpu: 1937.2741666666668 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/131072",
            "value": 3274.169283720893,
            "unit": "us/iter",
            "extra": "iterations: 215\ncpu: 3263.308837209306 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/262144",
            "value": 5079.4472794116955,
            "unit": "us/iter",
            "extra": "iterations: 136\ncpu: 5079.090441176472 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1024",
            "value": 4.0359441917556,
            "unit": "us/iter",
            "extra": "iterations: 174347\ncpu: 4.035852638703277 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/2048",
            "value": 8.115824936780559,
            "unit": "us/iter",
            "extra": "iterations: 86603\ncpu: 8.115431336096863 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/4096",
            "value": 16.179368847450203,
            "unit": "us/iter",
            "extra": "iterations: 44189\ncpu: 16.17846296589651 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/8192",
            "value": 31.969053507728592,
            "unit": "us/iter",
            "extra": "iterations: 21866\ncpu: 31.967250525930666 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/16384",
            "value": 63.296971121738956,
            "unit": "us/iter",
            "extra": "iterations: 11081\ncpu: 63.294603375146636 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/32768",
            "value": 125.83414511778591,
            "unit": "us/iter",
            "extra": "iterations: 5561\ncpu: 125.82927531019561 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/65536",
            "value": 246.29281933216902,
            "unit": "us/iter",
            "extra": "iterations: 2845\ncpu: 246.28369068541303 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/131072",
            "value": 495.1424368794502,
            "unit": "us/iter",
            "extra": "iterations: 1410\ncpu: 495.1141843971637 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/262144",
            "value": 4611.930464052212,
            "unit": "us/iter",
            "extra": "iterations: 153\ncpu: 4611.6254901960565 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/1024",
            "value": 0.6536595847457398,
            "unit": "us/iter",
            "extra": "iterations: 1072355\ncpu: 0.6536128427619574 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/2048",
            "value": 1.2864369924110606,
            "unit": "us/iter",
            "extra": "iterations: 544609\ncpu: 1.2863950099979997 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/4096",
            "value": 2.5537641828264235,
            "unit": "us/iter",
            "extra": "iterations: 274293\ncpu: 2.553660137152589 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/8192",
            "value": 5.106219088541539,
            "unit": "us/iter",
            "extra": "iterations: 137077\ncpu: 5.106143262545825 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/16384",
            "value": 10.330206126733279,
            "unit": "us/iter",
            "extra": "iterations: 67638\ncpu: 10.329761376740956 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/32768",
            "value": 20.654626832649807,
            "unit": "us/iter",
            "extra": "iterations: 33899\ncpu: 20.653464703973395 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/65536",
            "value": 41.582278072002374,
            "unit": "us/iter",
            "extra": "iterations: 16805\ncpu: 41.58204700981862 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/131072",
            "value": 83.14763040379908,
            "unit": "us/iter",
            "extra": "iterations: 8420\ncpu: 83.1423752969122 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< std::vector< int > >/262144",
            "value": 166.24240095124813,
            "unit": "us/iter",
            "extra": "iterations: 4205\ncpu: 166.23536266349606 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/1024",
            "value": 0.7375072475431134,
            "unit": "us/iter",
            "extra": "iterations: 931971\ncpu: 0.7374733763174982 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/2048",
            "value": 1.431121519659378,
            "unit": "us/iter",
            "extra": "iterations: 489715\ncpu: 1.4310680702041074 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/4096",
            "value": 2.8252151140075576,
            "unit": "us/iter",
            "extra": "iterations: 248273\ncpu: 2.825121136813107 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/8192",
            "value": 5.612539684066385,
            "unit": "us/iter",
            "extra": "iterations: 124773\ncpu: 5.612474653971591 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/16384",
            "value": 11.227804430582397,
            "unit": "us/iter",
            "extra": "iterations: 62520\ncpu: 11.22744561740242 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/32768",
            "value": 22.357188039379114,
            "unit": "us/iter",
            "extra": "iterations: 31286\ncpu: 22.355945151185793 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/65536",
            "value": 45.11578587054536,
            "unit": "us/iter",
            "extra": "iterations: 15542\ncpu: 45.11556427744138 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/131072",
            "value": 90.17609476534345,
            "unit": "us/iter",
            "extra": "iterations: 7756\ncpu: 90.17153171738002 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved< uti::vector< int > >/262144",
            "value": 180.17101312403904,
            "unit": "us/iter",
            "extra": "iterations: 3886\ncpu: 180.16286670097801 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1024",
            "value": 1.659373551006458,
            "unit": "us/iter",
            "extra": "iterations: 421672\ncpu: 1.659258380921661 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/2048",
            "value": 3.346535760150904,
            "unit": "us/iter",
            "extra": "iterations: 209465\ncpu: 3.346346167617479 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/4096",
            "value": 6.784689468946939,
            "unit": "us/iter",
            "extra": "iterations: 104434\ncpu: 6.784409291993025 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/8192",
            "value": 13.678522072599838,
            "unit": "us/iter",
            "extra": "iterations: 51240\ncpu: 13.678007416081133 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/16384",
            "value": 27.677081101336878,
            "unit": "us/iter",
            "extra": "iterations: 25351\ncpu: 27.67576821427154 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/32768",
            "value": 55.25430547004498,
            "unit": "us/iter",
            "extra": "iterations: 12669\ncpu: 55.25255347699137 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/65536",
            "value": 110.41027946978006,
            "unit": "us/iter",
            "extra": "iterations: 6337\ncpu: 110.40976802903607 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/131072",
            "value": 220.95716041601102,
            "unit": "us/iter",
            "extra": "iterations: 3173\ncpu: 220.94576110936075 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/262144",
            "value": 441.4013601265981,
            "unit": "us/iter",
            "extra": "iterations: 1580\ncpu: 441.3992405063292 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1024",
            "value": 2.0502729180725,
            "unit": "us/iter",
            "extra": "iterations: 336383\ncpu: 2.050212703971367 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/2048",
            "value": 4.063601232159253,
            "unit": "us/iter",
            "extra": "iterations: 172218\ncpu: 4.063572913400458 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/4096",
            "value": 8.097719088009622,
            "unit": "us/iter",
            "extra": "iterations: 86536\ncpu: 8.09755939724505 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/8192",
            "value": 16.236866692936903,
            "unit": "us/iter",
            "extra": "iterations: 43141\ncpu: 16.236385341090827 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/16384",
            "value": 32.56822818604691,
            "unit": "us/iter",
            "extra": "iterations: 21500\ncpu: 32.56599999999978 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/32768",
            "value": 65.49161607059922,
            "unit": "us/iter",
            "extra": "iterations: 10765\ncpu: 65.48707849512294 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/65536",
            "value": 130.5928465687164,
            "unit": "us/iter",
            "extra": "iterations: 5377\ncpu: 130.58601450622965 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/131072",
            "value": 260.67212439478357,
            "unit": "us/iter",
            "extra": "iterations: 2685\ncpu: 260.6617877094944 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/262144",
            "value": 522.1677518628763,
            "unit": "us/iter",
            "extra": "iterations: 1342\ncpu: 522.1407600596119 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}