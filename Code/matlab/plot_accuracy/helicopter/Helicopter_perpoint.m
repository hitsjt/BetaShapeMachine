set(0,'defaultaxesfontsize',24);
set(0,'defaultaxesfontname','Tahoma');
set(0,'defaultaxesfontweight','bold');
accury_deform = getaccuracy('accuracy_plot0_HELICOPTERS.txt');
accury_deform_box = getaccuracy('accuracy_plot0_HELICOPTERS_BOX.txt');
accury_deform_bsm = getaccuracy('accuracy_plotBSM_HELICOPTERS.txt');
accury_deform_bsm_box = getaccuracy('accuracy_plotBSM_HELICOPTERS_BOX.txt');
accury_peter = getaccuracy('peter_gt_helicopter.txt');
X=[0 0.00125 0.0025 0.00375 0.005 0.00625 0.0075 0.00875 0.01 0.01125 0.0125 0.01375 0.015 0.01625 0.0175 0.01875 0.02 0.02125 0.0225 0.02375 0.025 0.02625 0.0275 0.02875 0.03 0.03125 0.0325 0.03375 0.035 0.03625 0.0375 0.03875 0.04 0.04125 0.0425 0.04375 0.045 0.04625 0.0475 0.04875 0.05 0.05125 0.0525 0.05375 0.055 0.05625 0.0575 0.05875 0.06 0.06125 0.0625 0.06375 0.065 0.06625 0.0675 0.06875 0.07 0.07125 0.0725 0.07375 0.075 0.07625 0.0775 0.07875 0.08 0.08125 0.0825 0.08375 0.085 0.08625 0.0875 0.08875 0.09 0.09125 0.0925 0.09375 0.095 0.09625 0.0975 0.09875 0.1 0.10125 0.1025 0.10375 0.105 0.10625 0.1075 0.10875 0.11 0.11125 0.1125 0.11375 0.115 0.11625 0.1175 0.11875 0.12 0.12125 0.1225 0.12375 0.125 0.12625 0.1275 0.12875 0.13 0.13125 0.1325 0.13375 0.135 0.13625 0.1375 0.13875 0.14 0.14125 0.1425 0.14375 0.145 0.14625 0.1475 0.14875 0.15 0.15125 0.1525 0.15375 0.155 0.15625 0.1575 0.15875 0.16 0.16125 0.1625 0.16375 0.165 0.16625 0.1675 0.16875 0.17 0.17125 0.1725 0.17375 0.175 0.17625 0.1775 0.17875 0.18 0.18125 0.1825 0.18375 0.185 0.18625 0.1875 0.18875 0.19 0.19125 0.1925 0.19375 0.195 0.19625 0.1975 0.19875 0.2 0.20125 0.2025 0.20375 0.205 0.20625 0.2075 0.20875 0.21 0.21125 0.2125 0.21375 0.215 0.21625 0.2175 0.21875 0.22 0.22125 0.2225 0.22375 0.225 0.22625 0.2275 0.22875 0.23 0.23125 0.2325 0.23375 0.235 0.23625 0.2375 0.23875 0.24 0.24125 0.2425 0.24375 0.245 0.24625 0.2475 0.24875 ];
Yfinal = [0.000622193 0.00391526 0.00972745 0.0193487 0.0273158 0.0359051 0.0458298 0.0581371 0.0719164 0.0830551 0.101448 0.113467 0.12626 0.139766 0.154061 0.170238 0.186203 0.200407 0.214019 0.228314 0.246995 0.260623 0.278864 0.29715 0.313008 0.3253 0.344346 0.357776 0.372845 0.387793 0.403439 0.416793 0.43294 0.444761 0.458601 0.474156 0.488406 0.502549 0.515661 0.527604 0.541216 0.554252 0.565436 0.577607 0.589489 0.600219 0.610993 0.621768 0.632906 0.644273 0.655654 0.666687 0.67602 0.68681 0.69634 0.706598 0.715309 0.722548 0.731365 0.738892 0.746844 0.753551 0.759667 0.765752 0.771595 0.777832 0.784782 0.790564 0.796422 0.802704 0.807075 0.812325 0.816817 0.821856 0.826757 0.831189 0.834618 0.839581 0.84301 0.846986 0.849596 0.853496 0.857639 0.86116 0.863967 0.866775 0.869856 0.872435 0.875015 0.877853 0.880129 0.882132 0.885122 0.887793 0.890206 0.892497 0.895745 0.89881 0.900571 0.902543 0.904289 0.906368 0.908007 0.909782 0.911087 0.912908 0.914653 0.916019 0.918295 0.919828 0.921558 0.923152 0.9247 0.925731 0.926703 0.927932 0.929632 0.931195 0.932636 0.934032 0.935155 0.936354 0.93684 0.938008 0.938813 0.939996 0.941165 0.941893 0.943047 0.943987 0.94508 0.946294 0.947129 0.947933 0.948707 0.949284 0.949982 0.950953 0.951879 0.952304 0.953017 0.953715 0.954276 0.954717 0.95543 0.955946 0.956416 0.957023 0.957949 0.958632 0.959391 0.959861 0.960301 0.960832 0.961181 0.961682 0.963109 0.963776 0.964323 0.964747 0.965188 0.965764 0.96628 0.966569 0.966827 0.967176 0.967434 0.967858 0.968207 0.968678 0.969027 0.969361 0.969801 0.97018 0.970651 0.970969 0.971076 0.971501 0.971774 0.972001 0.972441 0.97276 0.973018 0.973367 0.973716 0.973898 0.97408 0.974399 0.974581 0.974718 0.974794 0.975021 0.975294 0.975446 0.97578 0.975856 0.976311 0.976433 0.976584 0.976706 ];
Yinit = [0.000773947 0.0052507 0.010638 0.0207145 0.0315649 0.0408219 0.0538121 0.0676824 0.082266 0.0936476 0.113254 0.125349 0.140054 0.154395 0.166945 0.185656 0.205339 0.219892 0.235553 0.249378 0.267285 0.282566 0.298288 0.313479 0.326864 0.339368 0.354559 0.367336 0.381009 0.394455 0.407673 0.419661 0.432773 0.44464 0.458055 0.471455 0.486555 0.498422 0.510046 0.521094 0.532172 0.54454 0.555208 0.567455 0.576879 0.586561 0.597957 0.608262 0.618717 0.628839 0.638142 0.647369 0.655305 0.665443 0.674426 0.684594 0.692 0.699618 0.707251 0.714186 0.722578 0.729938 0.736949 0.743945 0.749545 0.758073 0.764447 0.772186 0.779213 0.784403 0.790306 0.794843 0.80061 0.807181 0.812143 0.816468 0.820581 0.825528 0.829868 0.83474 0.838898 0.845529 0.851266 0.855697 0.858884 0.862966 0.866229 0.870114 0.872891 0.875971 0.878839 0.881844 0.886048 0.889189 0.891708 0.893605 0.897065 0.900965 0.903029 0.905229 0.906975 0.909327 0.912438 0.914122 0.915579 0.91737 0.91872 0.920678 0.922317 0.923941 0.92561 0.927325 0.928827 0.930178 0.93127 0.932196 0.934761 0.935884 0.937644 0.939283 0.939936 0.94115 0.942288 0.943805 0.945702 0.946643 0.948085 0.948935 0.950088 0.951226 0.952258 0.953169 0.954231 0.955232 0.95587 0.956613 0.957676 0.95892 0.959618 0.960635 0.961743 0.96238 0.962896 0.963503 0.964247 0.964611 0.965446 0.966128 0.966811 0.967191 0.967889 0.968238 0.969012 0.969452 0.969877 0.970211 0.970378 0.970818 0.971516 0.971789 0.972426 0.972821 0.973337 0.973747 0.97402 0.974126 0.974323 0.97449 0.974854 0.975826 0.976053 0.976296 0.976721 0.977024 0.977358 0.977905 0.97798 0.978375 0.9788 0.979103 0.979331 0.979498 0.979544 0.97971 0.980044 0.980135 0.980302 0.980545 0.980591 0.981137 0.981334 0.98141 0.981577 0.981744 0.981896 0.982017 0.982305 0.982305 0.982639 0.982912 ];
Ygtfinal= [0.000622193 0.00391526 0.00972745 0.0193487 0.0273158 0.0359051 0.0458298 0.0581371 0.0719164 0.0830551 0.101448 0.113467 0.12626 0.139766 0.154061 0.170238 0.186203 0.200407 0.214019 0.228314 0.246995 0.260623 0.278864 0.29715 0.313008 0.3253 0.344346 0.357776 0.372845 0.387793 0.403439 0.416793 0.43294 0.444761 0.458601 0.474156 0.488406 0.502549 0.515661 0.527604 0.541216 0.554252 0.565436 0.577607 0.589489 0.600219 0.610993 0.621768 0.632906 0.644273 0.655654 0.666687 0.67602 0.68681 0.69634 0.706598 0.715309 0.722548 0.731365 0.738892 0.746844 0.753551 0.759667 0.765752 0.771595 0.777832 0.784782 0.790564 0.796422 0.802704 0.807075 0.812325 0.816817 0.821856 0.826757 0.831189 0.834618 0.839581 0.84301 0.846986 0.849596 0.853496 0.857639 0.86116 0.863967 0.866775 0.869856 0.872435 0.875015 0.877853 0.880129 0.882132 0.885122 0.887793 0.890206 0.892497 0.895745 0.89881 0.900571 0.902543 0.904289 0.906368 0.908007 0.909782 0.911087 0.912908 0.914653 0.916019 0.918295 0.919828 0.921558 0.923152 0.9247 0.925731 0.926703 0.927932 0.929632 0.931195 0.932636 0.934032 0.935155 0.936354 0.93684 0.938008 0.938813 0.939996 0.941165 0.941893 0.943047 0.943987 0.94508 0.946294 0.947129 0.947933 0.948707 0.949284 0.949982 0.950953 0.951879 0.952304 0.953017 0.953715 0.954276 0.954717 0.95543 0.955946 0.956416 0.957023 0.957949 0.958632 0.959391 0.959861 0.960301 0.960832 0.961181 0.961682 0.963109 0.963776 0.964323 0.964747 0.965188 0.965764 0.96628 0.966569 0.966827 0.967176 0.967434 0.967858 0.968207 0.968678 0.969027 0.969361 0.969801 0.97018 0.970651 0.970969 0.971076 0.971501 0.971774 0.972001 0.972441 0.97276 0.973018 0.973367 0.973716 0.973898 0.97408 0.974399 0.974581 0.974718 0.974794 0.975021 0.975294 0.975446 0.97578 0.975856 0.976311 0.976433 0.976584 0.976706 ];
Yfuzzy = [ 0.000869831 0.00158706 0.00244163 0.004868 0.00898825 0.0133527 0.0177018 0.0210896 0.0240653 0.030032 0.0332519 0.0396002 0.0466656 0.0488173 0.0542194 0.0601862 0.0643827 0.0697543 0.0735388 0.0787426 0.0839005 0.090325 0.0938501 0.0996185 0.105265 0.112529 0.117595 0.124355 0.131985 0.137479 0.146711 0.151076 0.157699 0.163208 0.168396 0.173478 0.180833 0.186876 0.1944 0.204242 0.21204 0.219976 0.227545 0.235816 0.242683 0.252312 0.258187 0.266443 0.27653 0.285045 0.292889 0.300153 0.307523 0.31613 0.324142 0.331207 0.338746 0.348314 0.356219 0.363604 0.372791 0.382817 0.391683 0.400366 0.408332 0.416863 0.425057 0.436411 0.444758 0.450694 0.46159 0.469892 0.47595 0.483656 0.494583 0.502548 0.50998 0.516801 0.523501 0.531314 0.53841 0.546711 0.553746 0.562216 0.570639 0.577156 0.586052 0.59501 0.603189 0.608363 0.615672 0.622494 0.631116 0.637067 0.643797 0.648985 0.657439 0.664902 0.671372 0.679796 0.686724 0.694598 0.700687 0.707203 0.714055 0.720189 0.726797 0.733298 0.737769 0.742179 0.748436 0.754738 0.759683 0.764352 0.770426 0.776835 0.78329 0.788723 0.794613 0.800366 0.804761 0.810713 0.815016 0.81964 0.824081 0.827774 0.831619 0.836121 0.841126 0.844911 0.84897 0.854143 0.856966 0.859454 0.862567 0.865359 0.868015 0.87128 0.874378 0.877094 0.880482 0.883839 0.886495 0.889089 0.891653 0.893972 0.897482 0.900382 0.902091 0.9047 0.906104 0.9085 0.910652 0.912193 0.91439 0.915565 0.918144 0.922127 0.923531 0.926171 0.927606 0.929773 0.931451 0.932626 0.934 0.935739 0.937174 0.938227 0.939463 0.940989 0.942194 0.943186 0.944804 0.94633 0.947581 0.949092 0.950588 0.9519 0.952846 0.953838 0.954784 0.955517 0.956661 0.957363 0.958172 0.959545 0.960201 0.960995 0.961514 0.962658 0.963223 0.963879 0.964459 0.964642 0.965222 0.965649 0.966031 0.966428 0.966779 0.967328  ];
Yhuang = [0.000379386 0.00124439 0.00268605 0.00503824 0.00869552 0.0145988 0.0181498 0.0233095 0.0294252 0.0356471 0.0418083 0.0472866 0.053463 0.0612784 0.069033 0.0769242 0.0855742 0.095848 0.103421 0.112086 0.121844 0.13239 0.142619 0.151223 0.15957 0.16916 0.178357 0.189405 0.199693 0.209679 0.220393 0.229938 0.240197 0.250698 0.260957 0.271443 0.281656 0.291186 0.301824 0.313357 0.322144 0.333495 0.341356 0.352738 0.362708 0.372041 0.38277 0.392194 0.402559 0.409858 0.419965 0.430982 0.438494 0.449618 0.459588 0.468086 0.478254 0.489028 0.497253 0.507739 0.516678 0.525813 0.535374 0.545041 0.552689 0.559973 0.569382 0.577228 0.584239 0.592221 0.600431 0.608034 0.615394 0.622663 0.62887 0.636609 0.643954 0.650768 0.658098 0.664987 0.671315 0.677143 0.683516 0.689647 0.696067 0.700741 0.706826 0.712168 0.717176 0.722563 0.729635 0.734536 0.74003 0.744643 0.75003 0.754841 0.759196 0.764568 0.76947 0.775297 0.780533 0.784281 0.788242 0.792522 0.796695 0.7997 0.804298 0.808092 0.812037 0.816119 0.81923 0.822129 0.827258 0.830005 0.83345 0.837335 0.839778 0.843207 0.846592 0.849551 0.852404 0.855044 0.857791 0.860037 0.862753 0.864666 0.866927 0.869628 0.87195 0.874089 0.875516 0.877337 0.879553 0.88192 0.884211 0.885623 0.887444 0.888794 0.890206 0.891936 0.893438 0.894986 0.89705 0.89881 0.89963 0.901147 0.90271 0.903909 0.905078 0.90746 0.909221 0.910374 0.912225 0.913197 0.914593 0.915427 0.916945 0.918053 0.918781 0.919601 0.921649 0.922939 0.923668 0.924335 0.925565 0.926293 0.927219 0.928235 0.928903 0.929677 0.930148 0.931544 0.931923 0.932818 0.934867 0.935671 0.937462 0.937902 0.938555 0.939055 0.939602 0.940649 0.941362 0.941833 0.94244 0.943411 0.943836 0.944139 0.945277 0.94596 0.947098 0.947705 0.947994 0.948419 0.949026 0.949451 0.950012 0.950452 0.951029 0.951651 ];
fig = figure('Position', [0 0 825 450]);
plot(X, Yfinal*100, 'm', 'LineWidth', 3), hold all;
plot(X, accury_peter*100, 'r', 'LineWidth', 3), hold all;
%plot(X, accury_deform*100, '--g', 'LineWidth', 3), hold all;
%plot(X, accury_deform_bsm_box*100, 'b', 'LineWidth', 3), hold all;
plot(X, accury_deform_bsm*100, 'b', 'LineWidth', 3), hold all;
%plot(X, accury_deform_box*100, '--b', 'LineWidth', 3), hold all;

xlabel('Euclidean Distance');
ylabel('% Correspondences');
axis([0, 0.25, 0, 100]);
set(gca,'XTick',0:.05:.25);
set(gca,'YTick',0:10:100);
%legend('Our:all', 'Our:gtonly', 'Huang12:gtonly', 'Kim12:gtonly', 'Our:init', 'Location', 'SE');
%legend('Our:all', 'Our:gtonly', 'Huang12:gtonly', 'Huang12:1000', 'Kim12:gtonly', 'Our:init', 'Location', 'SE');
legend('Kim et al. 2013', 'Huang et al. 2013','Our method', 'Location', 'SE');
title('Helicopters');
fName = 'helicopter_perpoint.pdf';
% cmnpfx = '/Users/vk/Research/TalksAndPapers/2013/TemplateAnalysis/';
% outFile1 = [ cmnpfx 'nosvn/data/CorrespondenceResults/' fName];
% outFile2 = [ cmnpfx 'evolving_template/figures/quantitative/' fName];
% print(fig, '-dpdf', outFile1);
% %system(['/usr/texbin/pdfcrop ' outFile1 ' ' outFile2])
% ['pdfcrop ' outFile1 ' ' outFile2]
% close(fig);