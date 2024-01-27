window.BENCHMARK_DATA = {
  "lastUpdate": 1706352307379,
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
          "id": "c0723aa5aa8326d483fd77987213ab3821cabfbc",
          "message": "update benchmarks",
          "timestamp": "2024-01-27T11:36:29+01:00",
          "tree_id": "d7bb0be12fb64e0b7ae9c17ee156c0474f679551",
          "url": "https://github.com/eddieavd/uti/commit/c0723aa5aa8326d483fd77987213ab3821cabfbc"
        },
        "date": 1706352306459,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bm_push_back_trivial< std::vector< int > >/1024",
            "value": 0.8670596927853111,
            "unit": "us/iter",
            "extra": "iterations: 809076\ncpu: 0.867023246271055 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/2048",
            "value": 2.9100997902194488,
            "unit": "us/iter",
            "extra": "iterations: 238821\ncpu: 2.9098843904011797 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/4096",
            "value": 6.929550139358177,
            "unit": "us/iter",
            "extra": "iterations: 101178\ncpu: 6.926594714265951 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/8192",
            "value": 15.642353533548334,
            "unit": "us/iter",
            "extra": "iterations: 44785\ncpu: 15.641654571843246 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/16384",
            "value": 31.612281714311436,
            "unit": "us/iter",
            "extra": "iterations: 22143\ncpu: 31.610653479654978 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/32768",
            "value": 125.32253227248208,
            "unit": "us/iter",
            "extra": "iterations: 5593\ncpu: 125.21832647952797 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/65536",
            "value": 296.61858199492286,
            "unit": "us/iter",
            "extra": "iterations: 2366\ncpu: 296.56001690617063 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/131072",
            "value": 635.5405833333105,
            "unit": "us/iter",
            "extra": "iterations: 1104\ncpu: 635.5384963768115 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< std::vector< int > >/262144",
            "value": 1417.6860853659377,
            "unit": "us/iter",
            "extra": "iterations: 492\ncpu: 1417.6768292682932 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/1024",
            "value": 0.8750183355957671,
            "unit": "us/iter",
            "extra": "iterations: 799265\ncpu: 0.875014294382964 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/2048",
            "value": 1.6331590819471682,
            "unit": "us/iter",
            "extra": "iterations: 436184\ncpu: 1.6331488546118142 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/4096",
            "value": 3.049457536279334,
            "unit": "us/iter",
            "extra": "iterations: 229125\ncpu: 3.049462084015275 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/8192",
            "value": 5.918118447636113,
            "unit": "us/iter",
            "extra": "iterations: 118297\ncpu: 5.918129791964289 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/16384",
            "value": 11.645392628444878,
            "unit": "us/iter",
            "extra": "iterations: 60123\ncpu: 11.645405252565588 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/32768",
            "value": 24.57689085516582,
            "unit": "us/iter",
            "extra": "iterations: 30345\ncpu: 24.576272862086032 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/65536",
            "value": 45.97486886215839,
            "unit": "us/iter",
            "extra": "iterations: 15213\ncpu: 45.97429172418324 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/131072",
            "value": 91.97807893011773,
            "unit": "us/iter",
            "extra": "iterations: 7627\ncpu: 91.97747476071848 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_trivial< uti::vector< int > >/262144",
            "value": 184.07368957345776,
            "unit": "us/iter",
            "extra": "iterations: 3798\ncpu: 184.07235387045836 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/1024",
            "value": 7.014144941399347,
            "unit": "us/iter",
            "extra": "iterations: 103497\ncpu: 7.014046783964742 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/2048",
            "value": 13.941462582597326,
            "unit": "us/iter",
            "extra": "iterations: 50244\ncpu: 13.941358172120088 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/4096",
            "value": 27.48833582177564,
            "unit": "us/iter",
            "extra": "iterations: 25451\ncpu: 27.48840909983887 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/8192",
            "value": 55.45078767176926,
            "unit": "us/iter",
            "extra": "iterations: 12735\ncpu: 55.45038869257935 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/16384",
            "value": 109.82718629618101,
            "unit": "us/iter",
            "extra": "iterations: 6334\ncpu: 109.82745500473612 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/32768",
            "value": 950.1305274261092,
            "unit": "us/iter",
            "extra": "iterations: 711\ncpu: 949.9693389592109 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/65536",
            "value": 1936.4016160220647,
            "unit": "us/iter",
            "extra": "iterations: 362\ncpu: 1936.3422651933708 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/131072",
            "value": 3255.109036697397,
            "unit": "us/iter",
            "extra": "iterations: 218\ncpu: 3255.012385321109 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< std::vector< std::string > >/262144",
            "value": 5084.154637681118,
            "unit": "us/iter",
            "extra": "iterations: 138\ncpu: 5083.97101449276 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/1024",
            "value": 4.173805236965726,
            "unit": "us/iter",
            "extra": "iterations: 168189\ncpu: 4.173815172216969 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/2048",
            "value": 8.00433700012795,
            "unit": "us/iter",
            "extra": "iterations: 85997\ncpu: 8.004254799586002 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/4096",
            "value": 15.775054659938116,
            "unit": "us/iter",
            "extra": "iterations: 44786\ncpu: 15.774237484928356 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/8192",
            "value": 31.684761292940966,
            "unit": "us/iter",
            "extra": "iterations: 22182\ncpu: 31.681845640609414 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/16384",
            "value": 63.17438239005046,
            "unit": "us/iter",
            "extra": "iterations: 11096\ncpu: 63.172080028839225 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/32768",
            "value": 125.86187605684673,
            "unit": "us/iter",
            "extra": "iterations: 5559\ncpu: 125.85533369311032 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/65536",
            "value": 246.2095900774116,
            "unit": "us/iter",
            "extra": "iterations: 2842\ncpu: 246.21027445460865 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/131072",
            "value": 495.51444271570455,
            "unit": "us/iter",
            "extra": "iterations: 1414\ncpu: 495.4820367751075 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_nontrivial< uti::vector< std::string > >/262144",
            "value": 4682.578486842422,
            "unit": "us/iter",
            "extra": "iterations: 152\ncpu: 4682.199999999993 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/1024",
            "value": 0.6668663048995735,
            "unit": "us/iter",
            "extra": "iterations: 1050031\ncpu: 0.6668106941604589 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/2048",
            "value": 1.2999266717183828,
            "unit": "us/iter",
            "extra": "iterations: 538428\ncpu: 1.2998777923882046 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/4096",
            "value": 2.5737308787484485,
            "unit": "us/iter",
            "extra": "iterations: 272524\ncpu: 2.573604526573805 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/8192",
            "value": 5.109324874061312,
            "unit": "us/iter",
            "extra": "iterations: 136773\ncpu: 5.109338100356058 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/16384",
            "value": 10.329104052298906,
            "unit": "us/iter",
            "extra": "iterations: 67764\ncpu: 10.328947523758991 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/32768",
            "value": 20.64062200519289,
            "unit": "us/iter",
            "extra": "iterations: 33892\ncpu: 20.639929776938498 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/65536",
            "value": 41.31821860052844,
            "unit": "us/iter",
            "extra": "iterations: 16935\ncpu: 41.31757897844688 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/131072",
            "value": 82.8101013529577,
            "unit": "us/iter",
            "extra": "iterations: 8426\ncpu: 82.80610016615192 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< std::vector< int > >/262144",
            "value": 166.05823327005993,
            "unit": "us/iter",
            "extra": "iterations: 4214\ncpu: 166.04933554817185 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/1024",
            "value": 0.7490810859767029,
            "unit": "us/iter",
            "extra": "iterations: 938510\ncpu: 0.7490342138069928 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/2048",
            "value": 1.4580336590119758,
            "unit": "us/iter",
            "extra": "iterations: 480228\ncpu: 1.457986623020723 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/4096",
            "value": 2.890240696404692,
            "unit": "us/iter",
            "extra": "iterations: 242675\ncpu: 2.8900302874214523 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/8192",
            "value": 5.739892627363185,
            "unit": "us/iter",
            "extra": "iterations: 121856\ncpu: 5.739910221901231 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/16384",
            "value": 11.4624499811865,
            "unit": "us/iter",
            "extra": "iterations: 61127\ncpu: 11.462286714545126 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/32768",
            "value": 22.863526034318937,
            "unit": "us/iter",
            "extra": "iterations: 30479\ncpu: 22.863578201384442 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/65536",
            "value": 45.77733413885461,
            "unit": "us/iter",
            "extra": "iterations: 15311\ncpu: 45.77650055515656 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/131072",
            "value": 91.51994224725098,
            "unit": "us/iter",
            "extra": "iterations: 7636\ncpu: 91.51905447878447 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_trivial< uti::vector< int > >/262144",
            "value": 183.65285905512192,
            "unit": "us/iter",
            "extra": "iterations: 3810\ncpu: 183.64272965879292 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/1024",
            "value": 1.6008710123397503,
            "unit": "us/iter",
            "extra": "iterations: 436879\ncpu: 1.6007743562862886 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/2048",
            "value": 3.2718116135185378,
            "unit": "us/iter",
            "extra": "iterations: 213837\ncpu: 3.2716929249849294 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/4096",
            "value": 6.603568896173207,
            "unit": "us/iter",
            "extra": "iterations: 106167\ncpu: 6.603010351615845 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/8192",
            "value": 13.32165235496531,
            "unit": "us/iter",
            "extra": "iterations: 52591\ncpu: 13.321180430111584 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/16384",
            "value": 27.021418090839163,
            "unit": "us/iter",
            "extra": "iterations: 25980\ncpu: 27.019157043879954 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/32768",
            "value": 54.64234064212974,
            "unit": "us/iter",
            "extra": "iterations: 12770\ncpu: 54.6398433829283 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/65536",
            "value": 108.1955633585447,
            "unit": "us/iter",
            "extra": "iterations: 6479\ncpu: 108.19600246951713 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/131072",
            "value": 216.324493510512,
            "unit": "us/iter",
            "extra": "iterations: 3236\ncpu: 216.32061186650319 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< std::vector< std::string > >/262144",
            "value": 431.33175617284724,
            "unit": "us/iter",
            "extra": "iterations: 1620\ncpu: 431.3152469135838 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/1024",
            "value": 2.0481701227564235,
            "unit": "us/iter",
            "extra": "iterations: 341571\ncpu: 2.048157484095548 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/2048",
            "value": 4.071225018776036,
            "unit": "us/iter",
            "extra": "iterations: 171759\ncpu: 4.071149692301412 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/4096",
            "value": 8.192273157894906,
            "unit": "us/iter",
            "extra": "iterations: 85500\ncpu: 8.192105263157844 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/8192",
            "value": 16.358300675439587,
            "unit": "us/iter",
            "extra": "iterations: 42787\ncpu: 16.3574193096034 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/16384",
            "value": 32.799838298873574,
            "unit": "us/iter",
            "extra": "iterations: 21280\ncpu: 32.79963815789476 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/32768",
            "value": 66.06855988222665,
            "unit": "us/iter",
            "extra": "iterations: 10529\ncpu: 66.06486845854369 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/65536",
            "value": 132.11095778364358,
            "unit": "us/iter",
            "extra": "iterations: 5306\ncpu: 132.10614398793737 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/131072",
            "value": 263.5034896421888,
            "unit": "us/iter",
            "extra": "iterations: 2655\ncpu: 263.49190207156533 us\nthreads: 1"
          },
          {
            "name": "bm_push_back_reserved_nontrivial< uti::vector< std::string > >/262144",
            "value": 527.4982659654312,
            "unit": "us/iter",
            "extra": "iterations: 1331\ncpu: 527.4639368895587 us\nthreads: 1"
          }
        ]
      }
    ]
  }
}