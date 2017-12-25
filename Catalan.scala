object Solution {
  var cn = new Array[Long](1001)
    def catalan(n: Int): Long = 
        if (n <= 1) 1 
        else if(cn(n)==(-1)){
            var temp :Long = ((0 until n).map(i => ((catalan(i))%100000007 * (catalan(n - i - 1))%100000007)%100000007).sum)%100000007
            cn(n)=temp
            return temp
        }
        else cn(n)
    def main(args: Array[String]) {
        for( a <- 1 to 1000){
            cn(a)=(-1)
        }
       var t = readInt()
       for( a <- 1 to t){
           var n = readInt()
           println( "" + catalan(n) );
        }
    }
}
