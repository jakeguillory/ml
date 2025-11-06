#! /bin/bash


awk -F, '
{
    label = $NF;  # 0 or 1
    $NF = "";
    n = split($0, words, /[ ,]+/);
    for (i = 1; i <= n; i++) {
        w = words[i];
        if (w == "") continue;
        if (label == 1) spam[w]++;
        else ham[w]++;
    }
}
END {
    printf("%-20s %-10s %-10s\n", "word", "spam_count", "ham_count");
    for (w in spam) {
        printf("%-20s %-10d %-10d\n", w, spam[w], ham[w]+0);
    }
    for (w in ham) {
        if (!(w in spam))
            printf("%-20s %-10d %-10d\n", w, 0, ham[w]);
    }
}' emails_clean.csv > word_counts.txt

