#!/usr/bin/perl -w

$level=2;

open(OUT,">a.2")||die "Unable to create a.1, $!";

    print OUT <<EOF;
<!-- -*- xml -*- -->
<!DOCTYPE promptblock SYSTEM "promptblock.dtd">
<group name="Configuration">
EOF
    ;



$help="";
$val="";

sub mkhelp ()
{
    if ($help) {
	$help="\n  <help>$help</help>\n";
    }
}

sub clearhelp ()
{
    $help='';
}


while(<>){
    # Check for LEVELn

    if(/^LEVEL2 /) {
	next;
    } elsif(/^LEVEL([3-9])/i || /^LANG\s/){
	$level=$1 unless /^LANG/;
	$level++ if /^LANG/;

	print OUT "</group>\n";
	close OUT;

	open(OUT,">a.$level")||die "Unable to create a.$level, $!";
	print OUT "<!DOCTYPE promptblock SYSTEM \"promptblock.dtd\">\n";
	print OUT "<group name=\"Prompts\" lang=\"\" charset=\"\">\n";

	next;
    }

    # Check for setup strings

    elsif(/^(\S+)\s*\{(.*[^~]?)\}(.+)$/){ # Eeeeek! Looks like Befunge.
	# Single line field

	my ($id,$spec);
	($id,$val,$spec)=($1,$2,$3);



	# Number fields (N min max)

	if($spec=~/^\s*[NX]\s+([+-]?\d+)\s+([+-]?\d+)/i){
	    my ($min,$max)=($1,$2);
	    $val=~/^(.+)\s*(\d+)$/;
	    $val=$2;
	    my $desc=$1;
	    $desc=~s/\s+$//;

	    # Special case: keys (N 0 12[89])

	    mkhelp();
	    if($min==0 && ($max==128||$max==129)){
		print OUT "<key id=\"$id\" default=\"$val\"\n";
		print OUT "\tdesc=\"$desc\">$help$val</key>\n";
	    } else {
		print OUT "<int id=\"$id\" min=\"$min\" max=\"$max\" default=\"$val\"\n";
		print OUT "\tdesc=\"$desc\">$help$val</int>\n";
	    }
	    clearhelp();
	}

	
	# Boolean fields (B)

	elsif($spec=~/^\s*B/i){
	    $val=~/^(.+)\s*(YES|NO)$/i;
	    $val=$2;
	    my $desc=$1;
	    $desc=~s/\s+$//;
	    $val=0;
	    $val=1 if $val=~/YES/i;

	    mkhelp();
	    print OUT "<bool id=\"$id\" default=\"$val\"\n";
	    print OUT "\tdesc=\"$desc\">$help$val</bool>\n";
	    clearhelp();
	}


	# Character fields (C)

	elsif($spec=~/^\s*C/i){
	    $val=~/^(.+)\s*(.)$/i;
	    $val=$2;
	    my $desc=$1;
	    $desc=~s/\s+$//;

	    mkhelp();
	    print OUT "<char id=\"$id\" default=\"$val\"\n";
	    print OUT "\tdesc=\"$desc\">$help$val</char>\n";
	    clearhelp();
	}


	# Multiple choice token field (E)

	elsif($spec=~/^\s*[E]\s+(.+)$/i){
	    my $tokens=$1;
	    $val=~/^(.+)\s+(\S+)$/;
	    $val=$2;
	    my $desc=$1;
	    $desc=~s/\s+$//;

	    mkhelp();
	    print OUT "<select id=\"$id\" default=\"$val\"\n";
	    print OUT "\toptions=\"$tokens\"\n";
	    print OUT "\tdesc=\"$desc\">$help$val</select>\n";
	    clearhelp();
	}

	
	# String fields (S length description)

	elsif($spec=~/^\s*S\s+(\d+)\s+(.*)$/i){
	    my ($max,$desc)=($1,$2);
	    $desc=~s/\s+$//;

	    mkhelp();
	    print OUT "<string id=\"$id\" maxlength=\"$max\" default=\"$val\"\n";
	    print OUT "\tdesc=\"$desc\">$help$val</string\">\n";
	    clearhelp();
	}


	# Text blocks (T Description) -- one liners

	elsif($spec=~/^\s*T\s+(.*)$/i){
	    $desc=$1;
	    $desc=~s/\s+$//;

	    mkhelp();
	    print OUT "<text desc=\"$desc\"\nid=\"$id\">$help$val</text>\n\n";
	    clearhelp();
	}

 	else {
	    print OUT $_;
	}

	print OUT "\n";
	
    }

    elsif (/^LANGEND /) {
	next;
    }
    
    # Text blocks (T Description) -- multi-line ones

    elsif (/^(\S+)\s*\{(.*)$/){
	my $id=$1;
	my $text=$2;
	my $spec;
	while(<>){
	    if(/(.*[^~]?)\}(.+)$/){
		$text.=$1;
		$spec=$2;
		last;
	    }
	    $text.=$_;
	}
	$spec=~/\s*T\s+(\S.+\S)\s*$/;
	$desc=$1;
	print OUT "<text desc=\"$desc\"\nid=\"$id\">$text</text>\n\n";
    }


    else {
	$help.=$_ unless /^\s*$/;
    }
}

close OUT;


