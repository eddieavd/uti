window.BENCHMARK_DATA = {
  "lastUpdate": 1706352018858,
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
          "id": "c0723aa5aa8326d483fd77987213ab3821cabfbc",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T11:36:29+01:00",
          "tree_id": "d7bb0be12fb64e0b7ae9c17ee156c0474f679551",
          "url": "https://github.com/eddieavd/uti/commit/c0723aa5aa8326d483fd77987213ab3821cabfbc"
        },
        "date": 1706352017852,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back_trivial< std::vector< int > >/1024",
            "value": 0.8757765381163211,
            "unit": "us/iter",
            "extra": "iterations: 802280\ncpu: 0.875745375679314 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/2048",
            "value": 2.9150271395083,
            "unit": "us/iter",
            "extra": "iterations: 239319\ncpu: 2.9149001959727388 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/4096",
            "value": 6.934163285933731,
            "unit": "us/iter",
            "extra": "iterations: 100915\ncpu: 6.933990982510033 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/8192",
            "value": 15.009061933825633,
            "unit": "us/iter",
            "extra": "iterations: 46695\ncpu: 15.00882749759075 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/16384",
            "value": 30.97296576528532,
            "unit": "us/iter",
            "extra": "iterations: 22521\ncpu: 30.973051818302917 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/32768",
            "value": 125.10422936762573,
            "unit": "us/iter",
            "extra": "iterations: 5598\ncpu: 124.99640943194005 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/65536",
            "value": 295.101419721874,
            "unit": "us/iter",
            "extra": "iterations: 2373\ncpu: 295.0549936788874 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/131072",
            "value": 635.7314019963334,
            "unit": "us/iter",
            "extra": "iterations: 1102\ncpu: 635.6942831215977 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/262144",
            "value": 1403.0748436874078,
            "unit": "us/iter",
            "extra": "iterations: 499\ncpu: 1402.8981963927877 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/1024",
            "value": 0.8782439966103266,
            "unit": "us/iter",
            "extra": "iterations: 797716\ncpu: 0.8781981306630422 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/2048",
            "value": 1.6232345853938588,
            "unit": "us/iter",
            "extra": "iterations: 430517\ncpu: 1.6231784110731982 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/4096",
            "value": 3.502850485919777,
            "unit": "us/iter",
            "extra": "iterations: 229256\ncpu: 3.5027009107722327 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/8192",
            "value": 5.952373896675189,
            "unit": "us/iter",
            "extra": "iterations: 117939\ncpu: 5.952201561824322 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/16384",
            "value": 11.654114272396505,
            "unit": "us/iter",
            "extra": "iterations: 60067\ncpu: 11.654552416468274 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/32768",
            "value": 23.415584736138374,
            "unit": "us/iter",
            "extra": "iterations: 29940\ncpu: 23.416419505678 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/65536",
            "value": 46.35716592494195,
            "unit": "us/iter",
            "extra": "iterations: 15055\ncpu: 46.35596811690464 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/131072",
            "value": 92.26736414047802,
            "unit": "us/iter",
            "extra": "iterations: 7574\ncpu: 92.26666226564573 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/262144",
            "value": 184.1421861869768,
            "unit": "us/iter",
            "extra": "iterations: 3808\ncpu: 184.12226890756327 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1024",
            "value": 6.914133168498497,
            "unit": "us/iter",
            "extra": "iterations: 103538\ncpu: 6.913918561301191 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/2048",
            "value": 12.660712915940136,
            "unit": "us/iter",
            "extra": "iterations: 52772\ncpu: 12.659855605245228 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/4096",
            "value": 25.17291887714606,
            "unit": "us/iter",
            "extra": "iterations: 27822\ncpu: 25.171554884623713 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/8192",
            "value": 50.56158514064931,
            "unit": "us/iter",
            "extra": "iterations: 13971\ncpu: 50.561033569536846 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/16384",
            "value": 99.6479786324711,
            "unit": "us/iter",
            "extra": "iterations: 7020\ncpu: 99.64725071225075 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/32768",
            "value": 963.8276310679732,
            "unit": "us/iter",
            "extra": "iterations: 721\ncpu: 963.692510402217 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/65536",
            "value": 1952.3125798318063,
            "unit": "us/iter",
            "extra": "iterations: 357\ncpu: 1952.2249299719845 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/131072",
            "value": 3238.966275700911,
            "unit": "us/iter",
            "extra": "iterations: 214\ncpu: 3238.870093457947 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/262144",
            "value": 5142.931275362278,
            "unit": "us/iter",
            "extra": "iterations: 138\ncpu: 5142.412318840593 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1024",
            "value": 4.24110086220115,
            "unit": "us/iter",
            "extra": "iterations: 162955\ncpu: 4.24094688717745 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/2048",
            "value": 8.392653784625496,
            "unit": "us/iter",
            "extra": "iterations: 83139\ncpu: 8.392217852030939 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/4096",
            "value": 16.052304307527955,
            "unit": "us/iter",
            "extra": "iterations: 43157\ncpu: 16.051889612345676 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/8192",
            "value": 31.59115980036395,
            "unit": "us/iter",
            "extra": "iterations: 22040\ncpu: 31.589632486388396 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/16384",
            "value": 62.21733833780197,
            "unit": "us/iter",
            "extra": "iterations: 11190\ncpu: 62.21521894548698 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/32768",
            "value": 125.06558592354105,
            "unit": "us/iter",
            "extra": "iterations: 5598\ncpu: 125.06161128974632 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/65536",
            "value": 245.53523438596545,
            "unit": "us/iter",
            "extra": "iterations: 2850\ncpu: 245.52845614035152 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/131072",
            "value": 493.38691190981325,
            "unit": "us/iter",
            "extra": "iterations: 1419\ncpu: 493.3837914023958 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/262144",
            "value": 4582.346078431108,
            "unit": "us/iter",
            "extra": "iterations: 153\ncpu: 4582.277124182981 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/1024",
            "value": 0.6652599206311621,
            "unit": "us/iter",
            "extra": "iterations: 1052806\ncpu: 0.6652312011899661 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/2048",
            "value": 1.2999858652919851,
            "unit": "us/iter",
            "extra": "iterations: 539240\ncpu: 1.299936762851417 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/4096",
            "value": 2.571734823203218,
            "unit": "us/iter",
            "extra": "iterations: 272686\ncpu: 2.571621938786724 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/8192",
            "value": 5.114838639547414,
            "unit": "us/iter",
            "extra": "iterations: 137072\ncpu: 5.11477398739348 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/16384",
            "value": 10.348924449247741,
            "unit": "us/iter",
            "extra": "iterations: 67544\ncpu: 10.348716392277666 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/32768",
            "value": 20.99483202690906,
            "unit": "us/iter",
            "extra": "iterations: 33297\ncpu: 20.994494999549516 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/65536",
            "value": 41.76968981316228,
            "unit": "us/iter",
            "extra": "iterations: 16806\ncpu: 41.768529096750775 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/131072",
            "value": 83.35640834235113,
            "unit": "us/iter",
            "extra": "iterations: 8319\ncpu: 83.35093160235574 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/262144",
            "value": 166.56095462105216,
            "unit": "us/iter",
            "extra": "iterations: 4209\ncpu: 166.5543359467821 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/1024",
            "value": 0.7560117627481013,
            "unit": "us/iter",
            "extra": "iterations: 937451\ncpu: 0.7559730588585416 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/2048",
            "value": 1.4603725271628607,
            "unit": "us/iter",
            "extra": "iterations: 479055\ncpu: 1.4603312772019914 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/4096",
            "value": 2.889146065095904,
            "unit": "us/iter",
            "extra": "iterations: 242166\ncpu: 2.889014973200184 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/8192",
            "value": 5.748800239420518,
            "unit": "us/iter",
            "extra": "iterations: 121961\ncpu: 5.748781167750353 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/16384",
            "value": 11.45678971206216,
            "unit": "us/iter",
            "extra": "iterations: 61159\ncpu: 11.456555862587775 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/32768",
            "value": 23.165390164802282,
            "unit": "us/iter",
            "extra": "iterations: 30218\ncpu: 23.164481434906484 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/65536",
            "value": 46.01408370043835,
            "unit": "us/iter",
            "extra": "iterations: 15209\ncpu: 46.013827339075284 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/131072",
            "value": 91.90734567250993,
            "unit": "us/iter",
            "extra": "iterations: 7591\ncpu: 91.90517718350682 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/262144",
            "value": 183.50347507868975,
            "unit": "us/iter",
            "extra": "iterations: 3812\ncpu: 183.5030692549835 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1024",
            "value": 1.6280075856637677,
            "unit": "us/iter",
            "extra": "iterations: 430549\ncpu: 1.627925044536163 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/2048",
            "value": 3.308903984481198,
            "unit": "us/iter",
            "extra": "iterations: 211872\ncpu: 3.308805316417464 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/4096",
            "value": 6.7421945980721185,
            "unit": "us/iter",
            "extra": "iterations: 104148\ncpu: 6.7420929830625225 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/8192",
            "value": 13.484461010232552,
            "unit": "us/iter",
            "extra": "iterations: 51988\ncpu: 13.484177117796332 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/16384",
            "value": 27.446051453244873,
            "unit": "us/iter",
            "extra": "iterations: 25013\ncpu: 27.445860152720517 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/32768",
            "value": 54.445363133278,
            "unit": "us/iter",
            "extra": "iterations: 12830\ncpu: 54.44550272798144 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/65536",
            "value": 109.76178850683367,
            "unit": "us/iter",
            "extra": "iterations: 6369\ncpu: 109.7588946459415 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/131072",
            "value": 219.39245149135627,
            "unit": "us/iter",
            "extra": "iterations: 3185\ncpu: 219.38675039246536 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/262144",
            "value": 435.661519626177,
            "unit": "us/iter",
            "extra": "iterations: 1605\ncpu: 435.6662928348896 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1024",
            "value": 2.115083801752846,
            "unit": "us/iter",
            "extra": "iterations: 330900\ncpu: 2.115058325778185 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/2048",
            "value": 4.13958427810645,
            "unit": "us/iter",
            "extra": "iterations: 169000\ncpu: 4.139568639053225 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/4096",
            "value": 8.3436051535846,
            "unit": "us/iter",
            "extra": "iterations: 84058\ncpu: 8.343366485046072 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/8192",
            "value": 16.525250064955035,
            "unit": "us/iter",
            "extra": "iterations: 42337\ncpu: 16.525209627512453 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/16384",
            "value": 32.967354004801564,
            "unit": "us/iter",
            "extra": "iterations: 21237\ncpu: 32.96687856100196 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/32768",
            "value": 65.87196650311331,
            "unit": "us/iter",
            "extra": "iterations: 10598\ncpu: 65.8711077561803 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/65536",
            "value": 131.54772196130202,
            "unit": "us/iter",
            "extra": "iterations: 5323\ncpu: 131.54630847266563 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/131072",
            "value": 263.32724595712983,
            "unit": "us/iter",
            "extra": "iterations: 2659\ncpu: 263.3229409552473 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/262144",
            "value": 526.3092353383265,
            "unit": "us/iter",
            "extra": "iterations: 1330\ncpu: 526.3099248120278 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}