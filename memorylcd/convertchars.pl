
use strict;
use warnings;
use Fcntl ("SEEK_SET");

open(IN, '<', 'characters.901225-01.bin') || die "Failed to read chargen";

my $b = " ";

print "unsigned char c64font[128][8] = {\n";

my @chars_wanted = (
    32 .. 63, # space through question mark
    256, # at sign
    321 .. 346, # uppercase letters
    283 .. 288, # some punctuation (many not matching ASCII)
    257 .. 282, # lowercase letters
    347 .. 352, # misc box drawing characters that don't match ASCII at all
    #353 .. 383, # misc box drawing characters that don't match ASCII at all
    #0 .. 511, # full character set
);

my $charidx = 0;
my $last_seek_char = 0;

CHAR: foreach my $seek_char (@chars_wanted) {
    if ($seek_char != $last_seek_char + 1) {
        print "    // -----------------------------------\n";
    }
    $last_seek_char = $seek_char;
    my $seek_pos = $seek_char * 8;
    seek(IN, $seek_pos, SEEK_SET) || die "Failed to seek: $!";
    my $ascii_char = ($charidx + 32) . ($charidx < 95 ? " (".chr($charidx + 32).")" : "");
    print "    { // character $charidx, ascii $ascii_char, chargen index $seek_char, at $seek_pos bytes\n";
    for (0 .. 7) {
        my $read = read(IN, $b, 1);
        unless ($read == 1) {
            warn "Failed to read chargen index $seek_char: $!\n";
            next CHAR;
        }
        my $c = unpack("C", $b);
        print "        0b";
        for (my $bit = 0; $bit < 8; $bit++) {
            if ($c & (1 << $bit)) {
                print "1";
                }
            else {
                print "0";
            }
        }
        print ",\n";
    }
    print "    },\n";
    $charidx++;
}

print "};\n";

