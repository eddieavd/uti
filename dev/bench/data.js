window.BENCHMARK_DATA = {
  "lastUpdate": 1706343549616,
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
          "id": "333e83c79f6b09c34e70bb1aee3324208c0d323a",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T09:12:08+01:00",
          "tree_id": "5aab926d6b844426b4a2116da6e7fa7b4db65a08",
          "url": "https://github.com/eddieavd/uti/commit/333e83c79f6b09c34e70bb1aee3324208c0d323a"
        },
        "date": 1706343548676,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back< std::vector< int > >/512",
            "value": 0.507179200093929,
            "unit": "us/iter",
            "extra": "iterations: 1379737\ncpu: 0.5071462169964277 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/1024",
            "value": 0.869774816112616,
            "unit": "us/iter",
            "extra": "iterations: 805928\ncpu: 0.8697552386813711 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/4096",
            "value": 6.9172239994463665,
            "unit": "us/iter",
            "extra": "iterations: 101094\ncpu: 6.916903080301499 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/16384",
            "value": 30.97991045899219,
            "unit": "us/iter",
            "extra": "iterations: 22593\ncpu: 30.979121851901038 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/65536",
            "value": 295.5171852008491,
            "unit": "us/iter",
            "extra": "iterations: 2365\ncpu: 295.4297674418604 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< std::vector< int > >/131072",
            "value": 637.2262847985306,
            "unit": "us/iter",
            "extra": "iterations: 1092\ncpu: 637.1175824175822 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/512",
            "value": 0.5427938229959757,
            "unit": "us/iter",
            "extra": "iterations: 1299044\ncpu: 0.5427639864392582 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/1024",
            "value": 0.9760488057471405,
            "unit": "us/iter",
            "extra": "iterations: 717436\ncpu: 0.9759966045751821 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/4096",
            "value": 3.362451428016677,
            "unit": "us/iter",
            "extra": "iterations: 206055\ncpu: 3.3622265899881123 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/16384",
            "value": 12.982156850817699,
            "unit": "us/iter",
            "extra": "iterations: 54249\ncpu: 12.98143375914764 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/65536",
            "value": 51.05568744084466,
            "unit": "us/iter",
            "extra": "iterations: 13735\ncpu: 51.05402257007653 us\nthreads: 1"
          },
          {
            "name": "bm_push_back< uti::vector< int > >/131072",
            "value": 103.010520198334,
            "unit": "us/iter",
            "extra": "iterations: 6857\ncpu: 103.00507510573149 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}