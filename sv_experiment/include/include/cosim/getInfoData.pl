####################################################################
# Copyright 2003 Synopsys, Inc.   All Rights Reserved
# CoCentric (R) System Studio
#
# This is a perl based file that is invoked by the vcs script
# to read in the information contained in the csrc/sysc/info file.
#
####################################################################
my @listOfVdefFiles;
my $listOfVdefFilesCount = 0;
my @listOfSdefFiles;
my $listOfSdefFilesCount = 0;
my @listOfObjs;
my $listOfObjsCount = 0;

my $type = 0;
if ($ARGV[0] =~ /vdef/) {
    $type = 1;
} elsif ($ARGV[0] =~ /sdef/) {
    $type = 2;
}
shift;

my $i = 0;
my $throwAwayLine = <>;
$throwAwayLine = <>;
while (<>) {
   my @argList = split ':', $_;
   chop $argList[1];
   if ($argList[0] =~ /VDEF/) {
       $listOfVdefFiles[ $listOfVdefFilesCount++ ] = $argList[1];
   } elsif ($argList[0] =~ /SDEF/) {
       $listOfSdefFiles[ $listOfSdefFilesCount++ ] = "$argList[1]:a$i";
       $i++;
   } elsif ($argList[0] =~ /OBJECT/) {
       $listOfObjs[ $listOfObjsCount++ ] = $argList[1];
   }
}

if ($type == 1) {
    print STDOUT "@listOfVdefFiles\n";
} elsif ($type == 2) {
    print STDOUT "@listOfSdefFiles\n";
} else {
    print STDOUT "@listOfObjs\n";
}
