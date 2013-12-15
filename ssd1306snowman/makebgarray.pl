
open(F, '<', 'bg.gray');

my $c = '';
my $col = 0;

print "    ";

while (read(F, $c, 1)) {
    my $val = unpack('C', $c);
    printf "0b%08b,", $val;
    $col++;
    if ($col == (128 / 8)) {
        print "\n    ";
        $col = 0;
    }
    else {
        print " ";
    }
}
