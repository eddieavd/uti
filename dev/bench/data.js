window.BENCHMARK_DATA = {
  "lastUpdate": 1706344945755,
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
      }
    ]
  }
}