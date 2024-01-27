window.BENCHMARK_DATA = {
  "lastUpdate": 1706322033226,
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
          "id": "fc0e05a970f0896e7060a8fa1a601d50280f991c",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T03:05:26+01:00",
          "tree_id": "07c329fd16e7a9770c39bb4da02089c57c618802",
          "url": "https://github.com/eddieavd/uti/commit/fc0e05a970f0896e7060a8fa1a601d50280f991c"
        },
        "date": 1706321242600,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.5249531185279545,
            "unit": "us/iter",
            "extra": "iterations: 1322996\ncpu: 0.5248800449887983 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 7.62625965030547,
            "unit": "us/iter",
            "extra": "iterations: 91966\ncpu: 7.626028097340322 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 127.72689127663398,
            "unit": "us/iter",
            "extra": "iterations: 5491\ncpu: 127.61050810417049 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/262144",
            "value": 1407.2803366733986,
            "unit": "us/iter",
            "extra": "iterations: 499\ncpu: 1406.9891783567134 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2097152",
            "value": 8366.962373493865,
            "unit": "us/iter",
            "extra": "iterations: 83\ncpu: 8366.127710843377 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.5387115002133968,
            "unit": "us/iter",
            "extra": "iterations: 1295689\ncpu: 0.5386638305951502 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.3715877541999295,
            "unit": "us/iter",
            "extra": "iterations: 208104\ncpu: 3.371320109176182 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 25.847605692987575,
            "unit": "us/iter",
            "extra": "iterations: 27367\ncpu: 25.84538312566231 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/262144",
            "value": 204.24933421052617,
            "unit": "us/iter",
            "extra": "iterations: 3420\ncpu: 204.23850877193 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2097152",
            "value": 1637.5516098130856,
            "unit": "us/iter",
            "extra": "iterations: 428\ncpu: 1637.399065420558 us\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "49100975+eddieavd@users.noreply.github.com",
            "name": "eddieavd",
            "username": "eddieavd"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "d99611b1346f8fea1d230ddf32aa944e0954f23e",
          "message": "workflows (#6)\n\nadd testing and benchmarking workflows",
          "timestamp": "2024-01-27T03:18:01+01:00",
          "tree_id": "07c329fd16e7a9770c39bb4da02089c57c618802",
          "url": "https://github.com/eddieavd/uti/commit/d99611b1346f8fea1d230ddf32aa944e0954f23e"
        },
        "date": 1706322032250,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.5094134359541119,
            "unit": "us/iter",
            "extra": "iterations: 1371782\ncpu: 0.5093867684515471 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 7.589204231760992,
            "unit": "us/iter",
            "extra": "iterations: 92302\ncpu: 7.588933067539164 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/32768",
            "value": 126.60389127298805,
            "unit": "us/iter",
            "extra": "iterations: 5546\ncpu: 126.49527587450413 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/262144",
            "value": 1416.6561635992216,
            "unit": "us/iter",
            "extra": "iterations: 489\ncpu: 1416.5846625766874 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/2097152",
            "value": 8713.000037499796,
            "unit": "us/iter",
            "extra": "iterations: 80\ncpu: 8710.822499999998 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.5381466286064305,
            "unit": "us/iter",
            "extra": "iterations: 1293738\ncpu: 0.5381203922277923 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.3743379296706446,
            "unit": "us/iter",
            "extra": "iterations: 207339\ncpu: 3.3743439487988303 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/32768",
            "value": 26.78343190316476,
            "unit": "us/iter",
            "extra": "iterations: 25941\ncpu: 26.78293820592883 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/262144",
            "value": 204.25571266044315,
            "unit": "us/iter",
            "extra": "iterations: 3428\ncpu: 204.2502333722285 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/2097152",
            "value": 1629.6978624708283,
            "unit": "us/iter",
            "extra": "iterations: 429\ncpu: 1629.6013986013995 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}