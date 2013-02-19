(TeX-add-style-hook "120291"
 (lambda ()
    (LaTeX-add-bibitems
     "AIMA"
     "SSCPS"
     "Algorithms")
    (LaTeX-add-labels
     "itm:AIMA"
     "itm:SSCPS"
     "itm:algorithm")
    (TeX-run-style-hooks
     "graphicx"
     "setspace"
     "hyperref"
     "url"
     "color"
     "listings"
     "palatino"
     "geometry"
     "10pt}"
     "includefoot"
     "latex2e"
     "art11"
     "article"
     "a4paper"
     "11pt")))

